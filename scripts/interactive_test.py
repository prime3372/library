import sys
import os
import time
import subprocess
import threading

# arguments
gen = sys.argv[1]
sol = sys.argv[2]
act = sys.argv[3]
case_num = int(sys.argv[4])
include = sys.argv[5]

# variables
timelimit = 5000
timeout = 10000
opts = ["-I", include, "-O2", "-Wall", "-Wextra", "-fdiagnostics-color=always", "-std=c++23"]

# colors
RESET = "\033[0m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"

def pump(src, dst, prefix, f_log):
    try:
        for line in src:
            f_log.write(prefix + line)
            f_log.flush()
            dst.write(line)
            dst.flush()
    except Exception:
        pass

def main():
    print("compiling...")

    targets = [(gen, "gen.exe"), (sol, "sol.exe"), (act, "act.exe")]

    procs = [subprocess.Popen(["g++", src] + opts + ["-o", exe]) for src, exe in targets]

    failed = False
    for p in procs:
        if p.wait() != 0 and not failed:
            failed = True

    if failed:
        return

    print("compilation finished.")
    time.sleep(0.1)

    t_max = 0

    for i in range(1, case_num + 1):
        # run gen.exe
        try:
            with open("in.txt", "w") as f_in:
                subprocess.run(["./gen.exe"], stdout=f_in, timeout=timeout / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"Test {i} {BLUE}Aborted{RESET} {gen} timed out")
            break
        except subprocess.CalledProcessError:
            print(f"Test {i} {BLUE}Aborted{RESET} {gen} returned a non-zero exit status")
            break

        # run sol.exe
        p_sol = subprocess.Popen(["./sol.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
        p_act = subprocess.Popen(["./act.exe", "in.txt"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

        with open("log.txt", "w") as f_log:
            t1 = threading.Thread(target=pump, args=(p_sol.stdout, p_act.stdin, "   [send] ", f_log))
            t2 = threading.Thread(target=pump, args=(p_act.stdout, p_sol.stdin, "[receive] ", f_log))
            t1.start()
            t2.start()

            start = time.perf_counter()
            timedout = False
            while p_sol.poll() is None or p_act.poll() is None:
                if time.perf_counter() - start > timeout / 1000.0:
                    p_sol.kill()
                    p_act.kill()
                    timedout = True
                    break
                time.sleep(0.01)

            t1.join()
            t2.join()

        t = int((time.perf_counter() - start) * 1000)
        t_max = max(t_max, t)

        if timedout:
            print(f"Test {i} {YELLOW}Time Limit Exceeded{RESET} > {timeout} ms")
            break

        if p_sol.returncode != 0:
            print(f"Test {i} {MAGENTA}Runtime Error{RESET} {t} ms")
            break

        if p_act.returncode != 0:
            print(f"Test {i} {BLUE}Aborted{RESET} {act} returned a non-zero exit status")
            break

        if t > timelimit:
            print(f"Test {i} {YELLOW}Time Limit Exceeded{RESET} {t} ms")
            break

        print(f"Test {i} {GREEN}Passed{RESET} {t} ms")

        if i != case_num:
            subprocess.run(["cmd", "/c", "del", "in.txt", "log.txt"])
        else:
            print(f"All tests passed. [max {t_max} ms]")

if __name__ == "__main__":
    main()
    for f in ["sol.exe", "gen.exe", "act.exe"]:
        if os.path.exists(f):
            os.remove(f)