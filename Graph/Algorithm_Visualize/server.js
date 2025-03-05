let express = require('express');
let app = express();
const PORT = 3030;

const path = require('path')
app.use('/static', express.static(path.join(__dirname, '/src/public')))

console.log("Static folder path:", path.join(__dirname, '/src/public'));


app.get('/', (req,res) => {
    res.sendFile(__dirname + '/src/public/html/index.html');
})


app.listen(PORT, () => {
    console.log('Server is running at http://localhost:3030');
})

