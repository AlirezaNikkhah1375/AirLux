FROM python:alpine3.19
WORKDIR /app
COPY sender.py .
RUN pip3 install --no-cache-dir --upgrade requests
CMD [ "python3", "./sender.py"]