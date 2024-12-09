


#!/bin/bash

# Get the token from the first argument
# token="$1"

# # Echo the token for debugging (optional)
# echo "The token is: $token"

curl -X GET -H "Authorization: token $GITHUB_TOKEN \
          https://api.github.com/repos/infotechay/gke-cicd/environments/mysecret1/secrets >> output.txt