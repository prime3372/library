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
timeout = 10000
case_num = 50

# colors
CYAN = "\033[36m"
BLUE = "\033[34m"
YELLOW = "\033[33m"
MAGENTA = "\033[35m"
GREEN = "\033[32m"
RESET = "\033[0m"

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

    opts = ["-I", include, "-O2", "-Wall", "-Wextra", "-fdiagnostics-color=always", "-std=c++23"]

    for src, exe in [(sol, "sol.exe"), (gen, "gen.exe"), (act, "act.exe")]:
        if subprocess.run(["g++", src] + opts + ["-o", exe]).returncode != 0:
            if src == sol:
                print(f"{CYAN}Compile Error{RESET}")
            else:
                print(f"{BLUE}FAIL Compile Error {src}{RESET}")
            if os.path.exists(src):
                subprocess.run(["code", src], shell=True)
            return

    print("compilation finished")
    time.sleep(0.1)

    for i in range(1, case_num + 1):
        # run gen.exe
        try:
            with open("in.txt", "w") as f_in:
                subprocess.run(["./gen.exe"], stdout=f_in, timeout=timeout / 1000.0, check=True)
        except subprocess.TimeoutExpired:
            print(f"{BLUE}Test {i} FAIL Timed Out {gen}{RESET}")
            subprocess.run(["code", "in.txt"], shell=True)
            break
        except subprocess.CalledProcessError:
            print(f"{BLUE}Test {i} FAIL Runtime Error {gen}{RESET}")
            subprocess.run(["code", "in.txt"], shell=True)
            break

        # run sol.exe
        p_sol = subprocess.Popen(["./sol.exe"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
        p_act = subprocess.Popen(["./act.exe", "in.txt", "out.txt"], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

        with open("log.txt", "w") as f_log:
            t1 = threading.Thread(target=pump, args=(p_sol.stdout, p_act.stdin, "send    : ", f_log))
            t2 = threading.Thread(target=pump, args=(p_act.stdout, p_sol.stdin, "receive : ", f_log))
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
            print(f"{YELLOW}Test {i} Timed Out > {timeout} ms{RESET}")
            subprocess.run(["code", "in.txt", "log.txt", "out.txt"], shell=True)
            break

        if p_sol.returncode != 0:
            print(f"{MAGENTA}Test {i} Runtime Error {t} ms{RESET}")
            subprocess.run(["code", "in.txt", "log.txt", "out.txt"], shell=True)
            break

        if p_act.returncode != 0:
            print(f"{MAGENTA}Test {i} Interactor's Runtime Rrror {t} ms{RESET}")
            subprocess.run(["code", "in.txt", "log.txt", "out.txt"], shell=True)
            break

        print(f"{GREEN}Test {i} Success {t} ms{RESET}")

if __name__ == "__main__":
    main()
    for f in ["sol.exe", "gen.exe", "act.exe"]:
        if os.path.exists(f):
            os.remove(f)