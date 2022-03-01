#include "HscCollectDataModel.h"

HscCollectDataModel::HscCollectDataModel(quint64 id, quint64 moment, int chs)
    : m_id(id), m_moment(moment), m_chs(chs)
{
    qRegisterMetaType<HscCollectDataModel>("HscCollectDataModel");

    m_data.resize(m_chs);
    m_currentDateTime = QDateTime::currentDateTime();
}
