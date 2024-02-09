# Use a base image
FROM alpine

# Set the working directory
WORKDIR /app

# Copy the bash script into the container
COPY script.sh .

# Make the script executable
RUN chmod +x script.sh

# Install curl
RUN apk add --no-cache curl

# Execute the bash script when the container starts
CMD ["./script.sh"]
