const MAX_WIDTH = 1400;
const MAX_HEIGHT = 900;

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
        blobs = data.blobs;
        gameBlobs = data.gameBlobs.map(item => new Blob(parseInt(item.x), parseInt(item.y), parseInt(item.r)));
        break;
      case 'loggedIn':
        console.log('Logged in');
        gameBlobs = data.gameBlobs.map(item => new Blob(parseInt(item.x), parseInt(item.y), parseInt(item.r)));
        console.log('gameBlobs', gameBlobs);
        break;
      default:
        console.log('Unrecognized message');
        console.log(data);
        break;
    }
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

function draw() {
  background(0);

  translate(width / 2, height / 2);
  var newzoom = 64 / blob.r;
  zoom = lerp(zoom, newzoom, 0.1);
  scale(zoom);
  translate(-blob.pos.x, -blob.pos.y);

  for (let i = blobs.length - 1; i >= 0; i--) {
    const { id, x, y, r } = blobs[i];

    if (id !== socketId) {
      fill(0, 0, 255);
      ellipse(x, y, r * 2, r * 2);

      fill(255);
      textAlign(CENTER);
      textSize(4);
      text(id, x, y + r);
    }

    for (let i = gameBlobs.length-1; i >=0; i--) {
      gameBlobs[i].show();
      if (blob.eats(gameBlobs[i])) {
        score += 1;
        printScore();
        gameBlobs.splice(i, 1);
        let data = {
          messageType: "gameBlobEat",
          id: socketId,
          blobId: i,
        };
        socket.send(JSON.stringify(data));
        // if (gameBlobs.length < 10) {
        //   gameBlobs.push(new Blob(random(width), random(height), 8));
        // }
      }
    }
  }

  blob.show();

  if (mouseIsPressed) {
    blob.update();
  }

  //blob.constrain();

  let data = {
    messageType: "update",
    id: socketId,
    x: blob.pos.x.toString(),
    y: blob.pos.y.toString(),
    r: blob.r.toString()
  };

  if (socket.readyState === WebSocket.OPEN && new Date().getTime() - intervalDate.getTime() > 50) {
    socket.send(JSON.stringify(data));
    intervalDate = new Date();
  }
}
