#define _HSCPLOT_DLL_
#include "HscStaticCustPlot.h"

HscStaticCustPlot::HscStaticCustPlot(QWidget *parent) :
    QCustomPlot(parent)
{

}

HscStaticCustPlot::~HscStaticCustPlot()
{

}

void HscStaticCustPlot::setMouseControl(bool enable)
{
    if(enable)
    {
        // make left and bottom axes always transfer their ranges to right and top axes:
        connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)), this->xAxis2, SLOT(setRange(QCPRange)));
        connect(this->yAxis, SIGNAL(rangeChanged(QCPRange)), this->yAxis2, SLOT(setRange(QCPRange)));

        this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                              QCP::iSelectLegend | QCP::iSelectPlottables);
    }
    else
    {
        disconnect(this->xAxis,SIGNAL(rangeChanged(QCPRange)),0,0);
        disconnect(this->yAxis,SIGNAL(rangeChanged(QCPRange)),0,0);
        this->setInteractions(QCP::Interaction(!QCP::iRangeDrag | !QCP::iRangeZoom | !QCP::iSelectAxes |
                                               !QCP::iSelectLegend | !QCP::iSelectPlottables));
    }
}

void HscStaticCustPlot::selectionChanged()
{
    /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || this->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            this->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || this->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        this->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        this->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || this->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            this->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || this->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        this->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        this->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // synchronize selection of graphs with selection of corresponding legend items:
    for (int i=0; i<this->graphCount(); ++i)
    {
        QCPGraph *graph = this->graph(i);
        QCPPlottableLegendItem *item = this->legend->itemWithPlottable(graph);
        if (item->selected() || graph->selected())
        {
            item->setSelected(true);
            graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
        }
    }

}

void HscStaticCustPlot::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeDrag(this->xAxis->orientation());
    else if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeDrag(this->yAxis->orientation());
    else
        this->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}


void HscStaticCustPlot::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeZoom(this->xAxis->orientation());
    else if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        this->axisRect()->setRangeZoom(this->yAxis->orientation());
    else
        this->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void HscStaticCustPlot::titleDoubleClick(QMouseEvent* event)
{
    Q_UNUSED(event)
    if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender()))
    {
        // Set the plot title by double clicking on it
        bool ok;
        QString newTitle = QInputDialog::getText(this, "QCustomPlot example", "New plot title:", QLineEdit::Normal, title->text(), &ok);
        if (ok)
        {
            title->setText(newTitle);
            this->replot();
        }
    }
}

void HscStaticCustPlot::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    // Set an axis label by double clicking on it
    if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
    {
        bool ok;
        QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
        if (ok)
        {
            axis->setLabel(newLabel);
            this->replot();
        }
    }
}

void HscStaticCustPlot::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    // Rename a graph by double clicking on its legend item
    Q_UNUSED(legend)
    if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    {
        QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
        bool ok;
        QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
        if (ok)
        {
            plItem->plottable()->setName(newName);
            this->replot();
        }
    }
}

void HscStaticCustPlot::moveLegend()
{
    if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            this->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
            this->replot();
        }
    }
}

void HscStaticCustPlot::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
    // since we know we only have QCPGraphs in the plot, we can immediately access interface1D()
    // usually it's better to first check whether interface1D() returns non-zero, and only then use it.
    double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
    //  QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plottable->name()).arg(dataIndex).arg(dataValue);
    //  ui->statusBar->showMessage(message, 2500);
}

void HscStaticCustPlot::rescaleAllAxis()
{
    this->rescaleAxes(true);
    this->replot();
}


