curl -X GET -H "Authorization: token ${{ secrets.GITHUB_TOKEN }}" \
          https://api.github.com/repos/infotechay/gke-cicd/environments/mysecret1/secrets