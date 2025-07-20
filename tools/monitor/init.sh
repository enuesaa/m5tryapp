#!/bin/bash

until curl -s http://localhost:8086/ping; do
    echo 'Waiting for InfluxDB...'; sleep 1;
done

influx apply --file /dashboard.json \
    --org m5tryapp \
    --token m5tryapp
