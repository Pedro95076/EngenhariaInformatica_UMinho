#!/bin/bash

# Create backup directory inside the mongo container if it doesn't exist
docker exec -t mongo mkdir -p /backup

# Copy the backup archive to the mongo container
docker cp ./backup/ruas_archive.gz mongo:/backup/

# Perform the restore using mongorestore with the drop option to replace existing collections
docker exec -t mongo mongorestore --drop --archive=/backup/ruas_archive.gz --gzip
