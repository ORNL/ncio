# Run specific steps based on input

If($step -eq "configure")
{
  cd ${GITHUB_WORKSPACE}\..
  mkdir ncio-build
  cd ncio-build
  meson --prefix=${GITHUB_WORKSPACE}\..\ncio-install --default-library=static ${GITHUB_WORKSPACE}
}
ElseIf($step -eq "build")
{
  cd ${GITHUB_WORKSPACE}/../ncio-build
  ninja
}
ElseIf($step -eq "test")
{
  cd ${GITHUB_WORKSPACE}/../ncio-build
  ninja test
}
ElseIf($step -eq "install")
{
  cd ${GITHUB_WORKSPACE}/../ncio-build
  ninja install
}
