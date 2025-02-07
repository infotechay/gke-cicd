# Use an official Node.js runtime as a parent image
FROM node:20-slim

# Set working directory inside the container
WORKDIR /app

# Copy application files
COPY package.json server.js /app/

# Install dependencies
RUN npm install

# Expose the application port
EXPOSE 8080

# Command to run the application
CMD ["node", "server.js"]
