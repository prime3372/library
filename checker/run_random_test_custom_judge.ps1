g++ $Args[0] -o sol.exe -O2 -std=c++23
g++ $Args[1] -o gen.exe -O2 -std=c++23
g++ $Args[2] -o judge.exe -O2 -std=c++23

for ($i = 1; $i -le 20; $i++) {
  cmd /c ".\\gen.exe > in.txt"
  if ($LASTEXITCODE -ne 0) {
    Write-Host "Test" $i "Fail"
    code in.txt
    break
  }

  cmd /c ".\\sol.exe < in.txt > out.txt"
  if ($LASTEXITCODE -ne 0) {
    Write-Host "Test" $i "RE"
    code in.txt out.txt
    break
  }

  Get-Content "in.txt" | Set-Content "inout.txt"
  Get-Content "out.txt" | Add-Content "inout.txt"
  cmd /c ".\\judge.exe < inout.txt"
  if ($LASTEXITCODE -ne 0) {
    Write-Host "Test" $i "WA"
    code in.txt out.txt
    break
  }
  Write-Host "Test" $i "AC"
}

Remove-Item gen.exe; Remove-Item sol.exe; Remove-Item judge.exe; Remove-Item inout.txt