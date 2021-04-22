import fot_planner as fp
import time

x = fp.FotPlanner()
x.async_plan()
print(x.get_path())
time.sleep(0.3)
print(x.get_path())
time.sleep(0.3)
print(x.get_path())
time.sleep(0.3)

x.stop_plan()