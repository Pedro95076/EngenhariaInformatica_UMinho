#!/bin/bash

# Create backup directory inside the mongo container
docker exec -t mongo mkdir -p /backup

# Perform the backup using mongodump with archive option
docker exec -t mongo mongodump --db ruas --archive=/backup/ruas_archive.gz --gzip

# Copy the backup file from the container to the host
docker cp mongo:/backup/ruas_archive.gz ./backup/
