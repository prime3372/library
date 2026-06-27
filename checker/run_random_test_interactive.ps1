g++ $Args[0] -o sol.exe -O2 -std=c++23;
g++ $Args[1] -o gen.exe -O2 -std=c++23;

for ($i = 1; $i -le 20; $i++) {
  python checker/interactive.py ".\\gen.exe" ".\\sol.exe"
  if ($LASTEXITCODE -ne 0) {
    Write-Host "Test" $i "WA"
    code in.txt out.txt
    break
  }
  Write-Host "Test" $i "AC"
}

Remove-Item sol.exe; Remove-Item gen.exe