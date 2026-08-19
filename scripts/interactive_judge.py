import sys
import os
import time
import subprocess
import threading

# arguments
sol = sys.argv[1]
gen = sys.argv[2]
act = sys.argv[3]
include = sys.argv[4]

# variables
timelimit = 5000
timeout = 10000
case_num = 50
opts = ["-I", include, "-O2", "-Wall", "-Wextra", "-fdiagnostics-color=always", "-std=c++23"]

# colors
RED = "\033[31m"
GREEN = "\033[32m"
YELLOW = "\033[33m"
BLUE = "\033[34m"
MAGENTA = "\033[35m"
RESET = "\033[0m"

# results
OK = 0
WA = 1
PE = 2

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

    targets = [(sol, "sol.exe"), (gen, "gen.exe"), (act, "act.exe")]

    procs = [subprocess.Popen(["g++", src] + opts + ["-o", exe]) for src, exe in targets]

    failed = False
    for p in procs:
        if p.wait() != 0 and not failed:
            failed = True

    if failed:
        return

    print("compilation finished.")
    time.sleep(0.1)

    for i in range(1, case_num + 1):
        # run gen.exe
        try:
            with open("in.txt", "w") as f_in:
                subprocess.run(["./gen.exe"], stdout=f_in, timeout=timeout / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"{BLUE}Test {i} Fail Timed Out {gen}{RESET}")
            break
        except subprocess.CalledProcessError:
            print(f"{BLUE}Test {i} Fail Runtime Error {gen}{RESET}")
            break

        # run sol.exe and act.exe
        p_sol = subprocess.Popen(["./sol.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
        p_act = subprocess.Popen(["./act.exe", "in.txt"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

        with open("log.txt", "w") as f_log:
            t1 = threading.Thread(target=pump, args=(p_sol.stdout, p_act.stdin, "   [send] ", f_log))
            t2 = threading.Thread(target=pump, args=(p_act.stdout, p_sol.stdin, "[receive] ", f_log))
            t1.start()
            t2.start()

            start = time.perf_counter()
            tle = False
            while p_sol.poll() is None or p_act.poll() is None:
                if time.perf_counter() - start > timeout / 1000.0:
                    p_sol.kill()
                    p_act.kill()
                    tle = True
                    break
                time.sleep(0.01)

            t1.join()
            t2.join()

        t = int((time.perf_counter() - start) * 1000)

        if tle:
            print(f"{YELLOW}Test {i} TLE > {timeout} ms{RESET}")
            break

        if p_sol.returncode != 0:
            print(f"{MAGENTA}Test {i} RE {t} ms{RESET}")
            break

        if t > timelimit:
            print(f"{YELLOW}Test {i} TLE {t} ms{RESET}")
            break

        if p_act.returncode == OK:
            print(f"{GREEN}Test {i} AC {t} ms{RESET}")
            subprocess.run(["cmd", "/c", "del", "in.txt", "log.txt"])
        elif p_act.returncode == WA:
            print(f"{RED}Test {i} WA {t} ms{RESET}")
            break
        elif p_act.returncode == PE:
            print(f"{RED}Test {i} PE {t} ms{RESET}")
            break
        else:
            print(f"{BLUE}Test {i} Fail Runtime Error {act}{RESET}")
            break

if __name__ == "__main__":
    main()
    for f in ["sol.exe", "gen.exe", "act.exe"]:
        if os.path.exists(f):
            os.remove(f)