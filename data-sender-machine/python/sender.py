import random
import requests
from time import sleep

while True:
    url = "http://localhost:12345"
    index = 1
    payload = {"index": index, "data": random.randint(1, 1000)}

    # send POST request to an endpoint
    response = requests.post(url, data=payload)
    print(response.text)
    index += 1
    sleep(3)
    print("Waiting for 3 seconds . . .")
