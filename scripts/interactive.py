import sys
import os
import time
import subprocess
import math
import threading

# arguments
gen = sys.argv[1]
sol = sys.argv[2]
act = sys.argv[3]
case_num = int(sys.argv[4])
include = sys.argv[5]

# variables
timelimit = 5000
opts = ["-I", include, "-O2", "-Wall", "-Wextra", "-fdiagnostics-color=always", "-std=c++23"]

# exit status of the interactor
OK = [0]
WA = [1, 2]

def pump(src, dst, prefix, f_log):
    try:
        for line in src:
            f_log.write(prefix + line)
            f_log.flush()
            if dst:
                dst.write(line)
                dst.flush()
    except Exception:
        pass
    finally:
        if dst:
            try:
                dst.close()
            except Exception:
                pass

def main():
    RESET = "\033[0m"
    RED = "\033[31m"
    GREEN = "\033[32m"
    YELLOW = "\033[33m"
    BLUE = "\033[34m"
    MAGENTA = "\033[35m"

    print("compiling...")
    targets = [(gen, "gen.exe"), (sol, "sol.exe"), (act, "act.exe")]
    procs = [subprocess.Popen(["g++", src] + opts + ["-o", exe]) for src, exe in targets]

    failed = False
    for p in procs:
        if p.wait() != 0:
            failed = True

    if failed:
        print("compilation failed")
        return

    print("compilation finished")

    max_t = 0

    for i in range(1, case_num + 1):
        for f in ["in.txt", "log.txt"]:
            if os.path.exists(f):
                try:
                    os.remove(f)
                except Exception:
                    pass

        # run gen.exe
        try:
            with open("in.txt", "w") as f_in:
                subprocess.run(["./gen.exe"], stdout=f_in, timeout=timelimit * 1.1 / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"Test {i} {BLUE}Aborted{RESET} {gen} timed out")
            break
        except subprocess.CalledProcessError:
            print(f"Test {i} {BLUE}Aborted{RESET} {gen} returned a non-zero exit status")
            break

        # run sol.exe and act.exe
        p_sol = subprocess.Popen(["./sol.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
        p_act = subprocess.Popen(["./act.exe", "in.txt"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
        stopped = False

        with open("log.txt", "w") as f_log:
            t1 = threading.Thread(target=pump, args=(p_sol.stdout, p_act.stdin, "  [solution] ", f_log))
            t2 = threading.Thread(target=pump, args=(p_act.stdout, p_sol.stdin, "[interactor] ", f_log))
            t1.start()
            t2.start()

            start = time.perf_counter()
            while True:
                t = math.ceil((time.perf_counter() - start) * 1000)
                sol_code = p_sol.poll()
                act_code = p_act.poll()

                if time.perf_counter() - start > timelimit * 1.1 / 1000.0:
                    print(f"Test {i} {YELLOW}Time Limit Exceeded{RESET} > {timelimit} ms")
                    p_sol.kill()
                    p_act.kill()
                    stopped = True
                    break

                if sol_code is not None and sol_code != 0:
                    print(f"Test {i} {MAGENTA}Runtime Error{RESET} {t} ms")
                    p_act.kill()
                    stopped = True
                    break

                if act_code is not None and act_code not in OK:
                    if act_code in WA:
                        print(f"Test {i} {RED}Wrong Answer{RESET} {t} ms")
                    else:
                        print(f"Test {i} {BLUE}Aborted{RESET} {act} returned an unexpected exit status")
                    p_sol.kill()
                    stopped = True
                    break

                if sol_code is not None and act_code is not None:
                    break

                time.sleep(0.01)

            t1.join()
            t2.join()

        if stopped:
            break

        t = math.ceil((time.perf_counter() - start) * 1000)
        max_t = max(max_t, t)

        if t > timelimit:
            print(f"Test {i} {YELLOW}Time Limit Exceeded{RESET} > {timelimit} ms")
            break

        print(f"Test {i} {GREEN}Passed{RESET} {t} ms")

if __name__ == "__main__":
    main()
    for f in ["sol.exe", "gen.exe", "act.exe"]:
        if os.path.exists(f):
            try:
                os.remove(f)
            except Exception:
                pass