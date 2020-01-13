const MAX_WIDTH = 1400;
const MAX_HEIGHT = 900;
const REFRESH_RATE = 33;

let socket;
let blob;
let blobs = [];
let zoom = 1;
let gameBlobs = [];
let eatenUserBlobs = [];
let username;

const socketId = generateUUID();

function setup() {
  username = prompt('Please enter your username');

  createCanvas(MAX_WIDTH, MAX_HEIGHT);

  socket = new WebSocket("ws://localhost:3000/");
  socket.onmessage = (event) => {
    data = JSON.parse(event.data);
    switch (data.messageType) {
      case 'update':
        blobs = data.blobs.filter(item => !eatenUserBlobs.includes(blob => item.id === blob.id));
        gameBlobs = data.gameBlobs.map(item => new Blob(parseFloat(item.x), parseFloat(item.y), parseFloat(item.r)));
        updateScore(data.score);
        break;
      case 'loggedIn':
        gameBlobs = data.gameBlobs.map(item => new Blob(parseFloat(item.x), parseFloat(item.y), parseFloat(item.r)));
        updateHighScore(data.highscore);
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
      username,
      id: socketId,
    };

    socket.send(JSON.stringify(data));
  };

  blob = new Blob(random(width), random(height), 12);

  let data = {
    messageType: 'login',
    id: socketId,
    x: blob.position.x.toString(),
    y: blob.position.y.toString(),
    r: blob.radius.toString(),
    height: MAX_HEIGHT,
    width: MAX_WIDTH,
    username,
  };

  socket.onopen = () => {
    console.log("[open] Connection established");
    socket.send(JSON.stringify(data));
  };
}

let intervalDate = new Date();
let gameBlobInterval = new Date();

function draw() {
  background(0);

  translate(width / 2, height / 2);
  let newzoom = 64 / blob.radius;
  zoom = lerp(zoom, newzoom, 0.1);
  scale(zoom);
  translate(-blob.position.x, -blob.position.y);

  for (let i = gameBlobs.length-1; i >=0; i--) {
    gameBlobs[i].show();
    if (blob.eats(gameBlobs[i])) {
      const data = {
        messageType: "eatGameBlob",
        gameBlobId: i,
        id: socketId,
      };

      gameBlobs.splice(i, 1);

      if (new Date().getTime() - gameBlobInterval.getTime() > REFRESH_RATE) {
        socket.send(JSON.stringify(data));
        gameBlobInterval = new Date();
      }
    }
  }

  for (let i = blobs.length - 1; i >= 0; i--) {
    const { id, x, y, r, username } = blobs[i];
    const userBlob = new Blob(x, y, r, id);

    if (id !== socketId) {
      if (blob.eatsPlayer(userBlob)) {
        const data = {
          messageType: 'eatUserBlob',
          userBlobId: blobs[i].id,
          id: socketId,
        };

        blobs.splice(i, 1);
        eatenUserBlobs.push(userBlob);
        socket.send(JSON.stringify(data));

        continue;
      } else if (userBlob.eatsPlayer(blob)) {
        const userData = {
          messageType: 'eatUserBlob',
          userBlobId: socketId,
          id: blobs[i].id
        };

        // @TODO: remove score & background & terminate socket

        socket.send(JSON.stringify(userData));
        updateScore(0);

        const gameData = {
          messageType: 'logout',
          username,
          id: socketId,
        };

        socket.send(JSON.stringify(gameData));

        if (window.confirm('Game over!. Do you want to try again?')) {
          window.location.reload();
        }
      }

      fill(0, 0, 255);
      ellipse(x, y, r * 2, r * 2);

      fill(255);
      textAlign(CENTER);
      textSize(parseInt(r) - 2);
      text(username, parseFloat(x), parseFloat(y));
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

  const data = {
    messageType: "update",
    id: socketId,
    x: blob.position.x.toString(),
    y: blob.position.y.toString(),
    r: blob.radius.toString(),
    username,
  };

  if (socket.readyState === WebSocket.OPEN && new Date().getTime() - intervalDate.getTime() > REFRESH_RATE) {
    socket.send(JSON.stringify(data));
    intervalDate = new Date();
  }
}
