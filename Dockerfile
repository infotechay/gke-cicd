# # Use an official Node.js runtime as a parent image
# FROM node:20-slim

# # Set working directory inside the container
# WORKDIR /app

# # Copy application files
# COPY package.json server.js /app/

# # Install dependencies
# RUN npm install

# # Expose the application port
# EXPOSE 8080

# # Command to run the application
# CMD ["node", "server.js"]


# Stage 1: Build
FROM node:20 AS builder  # Use the latest stable version for security updates

WORKDIR /app
COPY package.json package-lock.json ./
RUN npm install --only=production

COPY . .
RUN npm run build  # Build the application

# Stage 2: Final runtime image
FROM node:20-alpine  # Use a minimal image for better security & efficiency

WORKDIR /app
COPY --from=builder /app/dist ./dist  # Copy only the built application
COPY --from=builder /app/node_modules ./node_modules
COPY --from=builder /app/package.json ./

EXPOSE 3000
CMD ["node", "dist/index.js"]
