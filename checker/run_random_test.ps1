# arguments
$checker = $Args[0]
$sol = $Args[1]
$gen = $Args[2]
$ans = $Args[3]
$timelimit = $Args[4]
$timeout = $Args[5]

do {

  g++ $checker -o checker.exe -std=c++23
  g++ $sol -o sol.exe -O2 -std=c++23 -Wall -Wextra; if ($LASTEXITCODE -ne 0) { break }
  g++ $gen -o gen.exe -O2 -std=c++23 -Wall -Wextra; if ($LASTEXITCODE -ne 0) { break }
  g++ $ans -o ans.exe -O2 -std=c++23 -Wall -Wextra; if ($LASTEXITCODE -ne 0) { break }

  for ($i = 1; $i -le 20; $i++) {
    # run gen.exe
    $p_gen = Start-Process -FilePath .\gen.exe -RedirectStandardOutput in.txt -PassThru -WindowStyle Hidden
    $dummy = $p_gen.Handle
    if (-not $p_gen.WaitForExit($timeout)) {
      $p_gen.Kill()
      Write-Host "Test" $i "Failed:" "Time Out" $gen -ForegroundColor Blue
      code in.txt
      break
    }
    if ($p_gen.ExitCode -ne 0) {
      Write-Host "Test" $i "Failed:" "Runtime Error" $gen -ForegroundColor Blue
      code in.txt
      break
    }

    # run ans.exe
    $p_ans = Start-Process -FilePath .\ans.exe -RedirectStandardInput in.txt -RedirectStandardOutput ans.txt -PassThru -WindowStyle Hidden
    $dummy = $p_ans.Handle
    if (-not $p_ans.WaitForExit($timeout)) {
      $p_ans.Kill()
      Write-Host "Test" $i "Failed:" "Time Out" $ans -ForegroundColor Blue
      code in.txt ans.txt
      break
    }
    if ($p_ans.ExitCode -ne 0) {
      Write-Host "Test" $i "Failed:" "Runtime Error" $ans -ForegroundColor Blue
      code in.txt ans.txt
      break
    }

    # run sol.exe
    $p_sol = Start-Process -FilePath .\sol.exe -RedirectStandardInput in.txt -RedirectStandardOutput out.txt -PassThru -WindowStyle Hidden
    $dummy = $p_sol.Handle
    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    if (-not $p_sol.WaitForExit($timeout)) {
      # time out
      $p_sol.Kill()
      Write-Host "Test" $i "TLE" ">" $timeout "ms" -ForegroundColor Yellow
      code in.txt out.txt ans.txt
      break
    }
    $stopwatch.Stop()
    $time = $stopwatch.ElapsedMilliseconds

    # RE check
    if ($p_sol.ExitCode -ne 0) {
      Write-Host "Test" $i "RE" $time "ms" -ForegroundColor Magenta
      code in.txt out.txt ans.txt
      break
    }

    # TLE check
    if ($time -gt $timelimit) {
      Write-Host "Test" $i "TLE" $time "ms" -ForegroundColor Yellow
      code in.txt out.txt ans.txt
      break
    }

    # WA check
    ./checker.exe out.txt ans.txt
    if ($LASTEXITCODE -ne 0) {
      Write-Host "Test" $i "WA" $time "ms" -ForegroundColor Red
      code in.txt out.txt ans.txt
      break
    }

    Write-Host "Test" $i "AC" $time "ms" -ForegroundColor Green
  }

} while ($false)

Remove-Item checker.exe
Remove-Item sol.exe -ErrorAction SilentlyContinue
Remove-Item gen.exe -ErrorAction SilentlyContinue
Remove-Item ans.exe -ErrorAction SilentlyContinue