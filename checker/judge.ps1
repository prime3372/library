# arguments
$sol = $Args[0]
$gen = $Args[1]
$ans = $Args[2]
$che = $Args[3]
$inc = $Args[4]

# constants
$timelimit = 5000
$timeout = 10000
$casesnum = 20

do {
  Write-Host "compiling..."

  g++ $sol -o sol.exe -I $inc -O2 -Wall -Wextra -fdiagnostics-color=always -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "CE" -ForegroundColor Cyan
    if (Test-Path $sol) { code $sol }
    break
  }

  g++ $gen -o gen.exe -I $inc -O2 -Wall -Wextra -fdiagnostics-color=always -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "FAIL" "Compile Error" $gen -ForegroundColor Blue
    if (Test-Path $gen) { code $gen }
    break
  }
  
  g++ $ans -o ans.exe -I $inc -O2 -Wall -Wextra -fdiagnostics-color=always -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "FAIL" "Compile Error" $ans -ForegroundColor Blue
    if (Test-Path $ans) { code $ans }
    break
  }
  
  g++ $che -o che.exe -I $inc -O2 -Wall -Wextra -fdiagnostics-color=always -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "FAIL" "Compile Error" $che -ForegroundColor Blue
    if (Test-Path $ans) { code $che }
    break
  }

  Write-Host "compilation finished"

  Start-Sleep -Milliseconds 100 # Start-Sleep is necessary when compilation completes very quickly.

  for ($i = 1; $i -le $casesnum; $i++) {
    # run gen.exe
    $p_gen = Start-Process -FilePath .\gen.exe -NoNewWindow -RedirectStandardOutput in.txt -PassThru
    $dummy = $p_gen.Handle
    if (-not $p_gen.WaitForExit($timeout)) {
      $p_gen.Kill()
      Write-Host "Test" $i "FAIL" "Timed Out" $gen -ForegroundColor Blue
      code in.txt
      break
    }
    if ($p_gen.ExitCode -ne 0) {
      Write-Host "Test" $i "FAIL" "Runtime Error" $gen -ForegroundColor Blue
      code in.txt
      break
    }

    # run ans.exe
    $p_ans = Start-Process -FilePath .\ans.exe -NoNewWindow -RedirectStandardInput in.txt -RedirectStandardOutput ans.txt -PassThru
    $dummy = $p_ans.Handle
    if (-not $p_ans.WaitForExit($timeout)) {
      $p_ans.Kill()
      Write-Host "Test" $i "FAIL" "Timed Out" $ans -ForegroundColor Blue
      code in.txt ans.txt
      break
    }
    if ($p_ans.ExitCode -ne 0) {
      Write-Host "Test" $i "FAIL" "Runtime Error" $ans -ForegroundColor Blue
      code in.txt ans.txt
      break
    }

    # run sol.exe
    $p_sol = Start-Process -FilePath .\sol.exe -NoNewWindow -RedirectStandardInput in.txt -RedirectStandardOutput out.txt -PassThru
    $dummy = $p_sol.Handle
    $stopwatch = [System.Diagnostics.Stopwatch]::StartNew()
    if (-not $p_sol.WaitForExit($timeout)) {
      $p_sol.Kill()
      Write-Host "Test" $i "TLE" ">" $timeout "ms" -ForegroundColor Yellow
      code in.txt out.txt ans.txt
      break
    }
    $stopwatch.Stop()
    $time = $stopwatch.ElapsedMilliseconds

    if ($p_sol.ExitCode -ne 0) {
      Write-Host "Test" $i "RE" $time "ms" -ForegroundColor Magenta
      code in.txt out.txt ans.txt
      break
    }

    if ($time -gt $timelimit) {
      Write-Host "Test" $i "TLE" $time "ms" -ForegroundColor Yellow 
      code in.txt out.txt ans.txt
      break
    }

    # run che.exe
    $p_che = Start-Process -FilePath .\che.exe -ArgumentList "in.txt","out.txt","ans.txt" -NoNewWindow -PassThru
    $dummy = $p_che.Handle
    if (-not $p_che.WaitForExit($timeout)) {
      $p_che.Kill()
      Write-Host "Test" $i "FAIL" "Timed Out" $che -ForegroundColor Blue
      code in.txt out.txt ans.txt
      break
    }
    if ($p_che.ExitCode -eq 1) {
      Write-Host "Test" $i "WA" $time "ms" -ForegroundColor Red
      code in.txt out.txt ans.txt
      break
    }
    if ($p_che.ExitCode -ne 0) {
      Write-Host "Test" $i "FAIL" "Runtime Error" $che -ForegroundColor Blue
      code in.txt out.txt ans.txt
      break
    }

    Write-Host "Test" $i "AC" $time "ms" -ForegroundColor Green
  }

} while ($false)

Remove-Item sol.exe -ErrorAction SilentlyContinue
Remove-Item gen.exe -ErrorAction SilentlyContinue
Remove-Item ans.exe -ErrorAction SilentlyContinue
Remove-Item che.exe -ErrorAction SilentlyContinue
