from threading import Timer
import time

def print_time():
    print("当前时间：%s" % time.ctime())
    global t
    fd = open("report.dat", "a")
    fd.write("\n28,20200507,17:02:34,719,9.22,9.42,507,9.37,0.715,1.86,14.28,282.0,272.0,271.1,270.1,65.2 ")
    fd.close()
    t = Timer(1, print_time)
    t.start()


t = Timer(1, print_time)
t.start()
