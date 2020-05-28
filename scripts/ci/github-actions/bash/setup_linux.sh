#!/bin/bash


case "${GH_JOBNAME}" in

  *"centos7"*)
    ${GITHUB_WORKSPACE}/scripts/ci/github-actions/bash/setup_centos7.sh
    ;;
    
esac
