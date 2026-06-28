import sys
import subprocess
import threading

def pipe_stream(src, dst, log_file):
    with open(log_file, 'w', buffering=1) as f:
        for line in iter(src.readline, ''):
            if not line:
                break
            dst.write(line)
            dst.flush()
            f.write(line)

def main():
    if len(sys.argv) < 3:
        sys.exit(1)

    cmd_sol = sys.argv[1]
    cmd_gen = sys.argv[2]

    p_sol = subprocess.Popen(cmd_sol, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
    p_gen = subprocess.Popen(cmd_gen, shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)

    t_in = threading.Thread(target=pipe_stream, args=(p_gen.stdout, p_sol.stdin, 'in.txt'))
    t_out = threading.Thread(target=pipe_stream, args=(p_sol.stdout, p_gen.stdin, 'out.txt'))

    t_in.start()
    t_out.start()

    p_sol.wait()
    t_out.join()

    try:
        p_gen.stdin.close()
    except Exception:
        pass

    p_gen.wait()
    t_in.join()

    sys.exit(p_gen.returncode)

if __name__ == '__main__':
    main()