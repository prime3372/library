# arguments
$sol = $Args[0]
$gen = $Args[1]
$ans = $Args[2]
$che = $Args[3]
$include = $Args[4]

# constants
$timelimit = 5000
$timeout = 10000
$case_num = 50
enum Result {
  ok = 0
  wa = 1
  pe = 2
}

do {
  Write-Host "compiling..."

  g++ $sol -I $include -O2 -Wall -Wextra -fdiagnostics-color=always -o sol.exe -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "CE" -ForegroundColor Cyan
    if (Test-Path $sol) { code $sol }
    break
  }

  g++ $gen -I $include -O2 -Wall -Wextra -fdiagnostics-color=always -o gen.exe -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "FAIL" "Compile Error" $gen -ForegroundColor Blue
    if (Test-Path $gen) { code $gen }
    break
  }

  g++ $ans -I $include -O2 -Wall -Wextra -fdiagnostics-color=always -o ans.exe -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "FAIL" "Compile Error" $ans -ForegroundColor Blue
    if (Test-Path $ans) { code $ans }
    break
  }

  g++ $che -I $include -O2 -Wall -Wextra -fdiagnostics-color=always -o che.exe -std=c++23
  if ($LASTEXITCODE -ne 0) {
    Write-Host "FAIL" "Compile Error" $che -ForegroundColor Blue
    if (Test-Path $ans) { code $che }
    break
  }

  Write-Host "compilation finished"

  Start-Sleep -Milliseconds 100

  for ($i = 1; $i -le $case_num; $i++) {
    # run gen.exe
    $p_gen = Start-Process -FilePath .\gen.exe -NoNewWindow -RedirectStandardOutput in.txt -PassThru
    $p_gen.Handle | Out-Null
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
    $p_ans.Handle | Out-Null
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
    $p_sol.Handle | Out-Null
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
    $p_che = Start-Process -FilePath .\che.exe -ArgumentList "in.txt", "out.txt", "ans.txt" -NoNewWindow -PassThru
    $p_che.Handle | Out-Null
    if (-not $p_che.WaitForExit($timeout)) {
      $p_che.Kill()
      Write-Host "Test" $i "FAIL" "Timed Out" $che -ForegroundColor Blue
      code in.txt out.txt ans.txt
      break
    }
    if ($p_che.ExistCode -eq [Result]::wa) {
      Write-Host "Test" $i "WA" $time "ms" -ForegroundColor Red
      code in.txt out.txt ans.txt
      break
    }
    if ($p_che.ExitCode -eq [Result]::pe) {
      Write-Host "Test" $i "PE" $time "ms" -ForegroundColor Red
      code in.txt out.txt ans.txt
      break
    }
    if ($p_che.ExitCode -ne [Result]::ok) {
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