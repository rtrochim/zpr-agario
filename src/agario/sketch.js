const MAX_WIDTH = 1400;
const MAX_HEIGHT = 900;
const REFRESH_RATE = 33;

let socket;
let blob;
let blobs = [];
let zoom = 1;
let gameBlobs = [];
let score = 0;
let socketId = Math.round((Math.random() * 100)).toString();
const printScore = () => {
  document.getElementById('score').innerHTML = 'Your score: ' + score;
};

function setup() {
  // const WIDTH = window.innerWidth <= MAX_WIDTH - 50 ? window.innerWidth - 50 : MAX_WIDTH;
  // const HEIGHT = window.innerHeight <= MAX_HEIGHT - 75 ? window.innerHeight - 75 : MAX_HEIGHT;

  createCanvas(MAX_WIDTH, MAX_HEIGHT);

  socket = new WebSocket("ws://localhost:3000/");
  socket.onmessage = (event) => {
    data = JSON.parse(event.data);
    switch (data.messageType) {
      case 'updateBlobs':
        score = data.score;
        blobs = data.blobs;
        gameBlobs = data.gameBlobs.map(item => new Blob(parseFloat(item.x), parseFloat(item.y), parseFloat(item.r)));
        printScore();
        break;
      case 'loggedIn':
        gameBlobs = data.gameBlobs.map(item => new Blob(parseFloat(item.x), parseFloat(item.y), parseFloat(item.r)));
        break;
      default:
        console.log('Unrecognized message');
        console.log(data);
        break;
    }
  };

  window.onunload = () => {
    const data = {
      messageType: 'logout',
      id: socketId,
    };

    socket.send(JSON.stringify(data));
  };
  printScore();
  blob = new Blob(random(width), random(height), random(8, 24));

  let data = {
    messageType: "login",
    id: socketId,
    x: blob.pos.x.toString(),
    y: blob.pos.y.toString(),
    r: blob.r.toString(),
    height: MAX_HEIGHT,
    width: MAX_WIDTH
  };

  socket.onopen = (e) => {
    console.log("[open] Connection established");
    console.log("Sending to server");
    socket.send(JSON.stringify(data));
  };
}

let intervalDate = new Date();
let gameBlobInterval = new Date();

function draw() {
  background(0);

  translate(width / 2, height / 2);
  let newzoom = 64 / blob.r;
  zoom = lerp(zoom, newzoom, 0.1);
  scale(zoom);
  translate(-blob.pos.x, -blob.pos.y);

  for (let i = blobs.length - 1; i >= 0; i--) {
    const { id, x, y, r } = blobs[i];

    if (id !== socketId) {
      if (blob.eatsPlayer(new Blob(x, y, r))) {
        // const data = {
        //   messageType: 'userBlobEat',
        //   userBlobId: blobs[i].id,
        //   id: socketId,
        // };

        // blobs.splice(i, 1);
        // socket.send(JSON.stringify(data));
        // continue;
      }

      fill(0, 0, 255);
      ellipse(x, y, r * 2, r * 2);

      fill(255);
      textAlign(CENTER);
      textSize(4);
      text(id, x, y + r);
    }
  }

  for (let i = gameBlobs.length-1; i >=0; i--) {
    gameBlobs[i].show();
    if (blob.eats(gameBlobs[i])) {
      const data = {
        messageType: "gameBlobEat",
        blobId: socketId,
        gameBlobId: i,
        id: socketId,
      };

      if (new Date().getTime() - gameBlobInterval.getTime() > REFRESH_RATE) {
        gameBlobs.splice(i, 1);
        socket.send(JSON.stringify(data));
        gameBlobInterval = new Date();
      }
    }
  }

  // Draw arena walls
  stroke('white');
  strokeWeight(4);
  line(-MAX_WIDTH,MAX_HEIGHT,MAX_WIDTH,MAX_HEIGHT);
  line(-MAX_WIDTH,-MAX_HEIGHT,MAX_WIDTH,-MAX_HEIGHT);
  line(MAX_WIDTH,-MAX_HEIGHT,MAX_WIDTH,MAX_HEIGHT);
  line(-MAX_WIDTH,-MAX_HEIGHT,-MAX_WIDTH,MAX_HEIGHT);
  noStroke();

  blob.show();

  if (mouseIsPressed) {
    blob.update();
  }

  blob.constrain();

  let data = {
    messageType: "update",
    id: socketId,
    x: blob.pos.x.toString(),
    y: blob.pos.y.toString(),
    r: blob.r.toString()
  };

  if (socket.readyState === WebSocket.OPEN && new Date().getTime() - intervalDate.getTime() > REFRESH_RATE) {
    socket.send(JSON.stringify(data));
    intervalDate = new Date();
  }
}
