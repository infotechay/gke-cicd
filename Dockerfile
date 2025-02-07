# Use a lightweight base image
FROM gcr.io/distroless/base-debian10

# Set working directory
WORKDIR /app

# Copy application files (assuming a Node.js app)
COPY server.js package.json /app/

# Install dependencies
RUN apt-get update && apt-get install -y nodejs npm && npm install

# Expose application port
EXPOSE 8080

# Start the application
CMD ["node", "server.js"]
