const express = require('express');
const serveIndex = require("serve-index");
const app = express();
app.use('/repo', express.static('repo'));
app.use('/repo', serveIndex('repo', { icons: true }))
app.use(express.static('public'));

app.listen(3000, () => {
  console.log('Server running on http://localhost:3000');
})
