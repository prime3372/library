from enum import Enum
import sys
import subprocess
import threading

timeout_sec = 5.0

def pipe_stream(src, dst, log_file):
    with open(log_file, 'w', buffering=1) as f:
        for line in iter(src.readline, ''):
            if not line:
                break

            try:
                dst.write(line)
                dst.flush()
            except OSError:
                pass

            f.write(line)

def main():
    if len(sys.argv) < 4:
        print('FAIL too few arguments')
        sys.exit(2)

    cmd_sol = sys.argv[1]
    cmd_gen = sys.argv[2]
    test = sys.argv[3]

    p_sol = subprocess.Popen(cmd_sol, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    p_gen = subprocess.Popen(cmd_gen, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

    t_in = threading.Thread(target=pipe_stream, args=(p_gen.stdout, p_sol.stdin, 'in.txt'))
    t_out = threading.Thread(target=pipe_stream, args=(p_sol.stdout, p_gen.stdin, 'out.txt'))

    t_in.start()
    t_out.start()

    try:
        p_sol.wait(timeout=timeout_sec)
    except subprocess.TimeoutExpired:
        subprocess.run(['taskkill', '/F', '/T', '/PID', str(p_sol.pid)], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        subprocess.run(['taskkill', '/F', '/T', '/PID', str(p_gen.pid)], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        t_out.join()
        t_in.join()
        print('Test', test, 'TLE')
        sys.exit(1)

    t_out.join()

    try:
        p_gen.stdin.close()
    except Exception:
        pass
    
    try:
        p_gen.wait(timeout=timeout_sec)
    except subprocess.TimeoutExpired:
        subprocess.run(['taskkill', '/F', '/T', '/PID', str(p_gen.pid)], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        t_in.join()
        print('Test', test, 'FAIL the judge program timed out')
        sys.exit(2)

    t_in.join()

    if p_sol.returncode != 0:
        print('Test', test, 'RE')
        sys.exit(1)

    if p_gen.returncode != 0:
        print('Test', test, 'WA')
        sys.exit(1)

    print('Test', test, 'AC')
    sys.exit(0)

if __name__ == '__main__':
    main()