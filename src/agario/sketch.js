const MAX_WIDTH = 1400;
const MAX_HEIGHT = 900;
const REFRESH_RATE = 33;
const BLOB_DEFAULT_RADIUS = 12;
const DEFAULT_ZOOM = 64;
const LERP_RATIO = 0.1;
const STROKE_WEIGHT = 4;

let socket;
let blob;
let blobs = [];
let zoom = 1;
let gameBlobs = [];
let eatenUserBlobs = [];
let username;

const socketId = generateUUID();

const MESSAGE_TYPES = {
  EAT_GAME_BLOB: 'eatGameBlob',
  EAT_USER_BLOB: 'eatUserBlob',
  LOGGED_IN: 'loggedIn',
  LOGIN: 'login',
  LOGOUT: 'logout',
  UPDATE: 'update',
};

function setup() {
  username = prompt('Podaj swoją nazwę użytkownika');

  createCanvas(MAX_WIDTH, MAX_HEIGHT);

  socket = new WebSocket("ws://localhost:3000/");
  socket.onmessage = (event) => {
    data = JSON.parse(event.data);
    switch (data.messageType) {
      case MESSAGE_TYPES.UPDATE:
        blobs = data.blobs.filter(item => !eatenUserBlobs.includes(blob => item.id === blob.id));
        gameBlobs = data.gameBlobs.map(item => new Blob(parseFloat(item.x), parseFloat(item.y), parseFloat(item.r)));
        updateScore(data.score);
        break;
      case MESSAGE_TYPES.LOGGED_IN:
        gameBlobs = data.gameBlobs.map(item => new Blob(parseFloat(item.x), parseFloat(item.y), parseFloat(item.r)));
        updateHighScore(data.highscore);
        break;
      default:
        console.log('Unrecognized message');
        console.log(data);
        break;
    }
  };

  window.onbeforeunload = () => {
    const data = {
      messageType: MESSAGE_TYPES.LOGOUT,
      username,
      id: socketId,
    };

    socket.send(JSON.stringify(data));
  };

  blob = new Blob(random(width), random(height), BLOB_DEFAULT_RADIUS);

  let data = {
    messageType: MESSAGE_TYPES.LOGIN,
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
  let newzoom = DEFAULT_ZOOM / blob.radius;
  zoom = lerp(zoom, newzoom, LERP_RATIO);
  scale(zoom);
  translate(-blob.position.x, -blob.position.y);

  for (let i = gameBlobs.length-1; i >=0; i--) {
    gameBlobs[i].show();
    if (blob.eats(gameBlobs[i])) {
      const data = {
        messageType: MESSAGE_TYPES.EAT_GAME_BLOB,
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
          messageType: MESSAGE_TYPES.EAT_USER_BLOB,
          userBlobId: blobs[i].id,
          id: socketId,
        };

        blobs.splice(i, 1);
        eatenUserBlobs.push(userBlob);
        socket.send(JSON.stringify(data));

        continue;
      } else if (userBlob.eatsPlayer(blob)) {
        const userData = {
          messageType: MESSAGE_TYPES.EAT_USER_BLOB,
          userBlobId: socketId,
          id: blobs[i].id
        };

        socket.send(JSON.stringify(userData));
        updateScore(0);

        const gameData = {
          messageType: MESSAGE_TYPES.LOGOUT,
          username,
          id: socketId,
        };

        socket.send(JSON.stringify(gameData));

        if (window.confirm('Koniec gry!. Czy chcesz spróbować ponownie?')) {
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
  strokeWeight(STROKE_WEIGHT);
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
    messageType: MESSAGE_TYPES.UPDATE,
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
