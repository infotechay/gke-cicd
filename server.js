const http = require('http');

// Define the port
const PORT = 8080;

// Create a server that responds with "Hello World!"
const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');
  res.end('Hello World! Lets get it done asap \n');
});

// Start the server
server.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}/`);
});
