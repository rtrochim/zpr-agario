const MAX_WIDTH = 1400;
const MAX_HEIGHT = 900;

let socket;
let blob;
let blobs = [];
let zoom = 1;
let gameBlobs = [];
let score = 0;

const printScore = () => {
  document.getElementById('score').innerHTML = 'Your score: ' + score;
}

function setup() {
  const WIDTH = window.innerWidth <= MAX_WIDTH - 50 ? window.innerWidth - 50 : MAX_WIDTH;
  const HEIGHT = window.innerHeight <= MAX_HEIGHT - 75 ? window.innerHeight - 75 : MAX_HEIGHT;

  createCanvas(WIDTH, HEIGHT);
  // Start a socket connection to the server
  // Some day we would run this server somewhere else
  socket = io.connect('http://localhost:3000');
  printScore();

  blob = new Blob(random(width), random(height), random(8, 24));

  for (let i = 0; i < 200; i++) {
    const x = random(-width,width);
    const y = random(-height,height);
    gameBlobs[i] = new Blob(x, y, 8);
  }

  // Make a little object with  and y
  const data = {
    x: blob.pos.x,
    y: blob.pos.y,
    r: blob.r
  };

  socket.emit('start', data);
  socket.on('heartbeat', (data) => {
      blobs = data;
  });
}

function draw() {
  background(0);

  translate(width / 2, height / 2);
  var newzoom = 64 / blob.r;
  zoom = lerp(zoom, newzoom, 0.1);
  scale(zoom);
  translate(-blob.pos.x, -blob.pos.y);

  for (let i = blobs.length - 1; i >= 0; i--) {
    const { id, x, y, r } = blobs[i];

    if (id !== socket.id) {
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
        if (gameBlobs.length < 10) {
          gameBlobs.push(new Blob(random(width), random(height), 8));
        }
      }
    }
  }

  blob.show();

  if (mouseIsPressed) {
    blob.update();
  }

  // blob.constrain();

  const data = {
    x: blob.pos.x,
    y: blob.pos.y,
    r: blob.r
  };

  socket.emit('update', data);
}
