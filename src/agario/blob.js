const GAME_BLOB_RATIO = 1.5;
const USER_BLOB_RATIO = 1.5;
const LEPR_RATIO = 0.2;
const COLOUR_WHITE = 255;
const BASE_VELOCITY = 3;

function Blob(x, y, radius) {
  this.position = createVector(x, y, 0);
  this.radius = radius;
  this.velocity = createVector(0, 0, 0);

  this.update = () => {
    const newVelocity = createVector((mouseX - width / 2), (mouseY - height / 2));
    newVelocity.limit(BASE_VELOCITY - (this.radius / 100));
    this.velocity.lerp(newVelocity, LEPR_RATIO);
    this.position.add(this.velocity);
  };

  this.eats = (other) => {
    const distance = p5.Vector.dist(this.position, other.position);
    if (distance < this.radius + other.radius) {
      const sum = PI * this.radius * this.radius + PI * other.radius / (GAME_BLOB_RATIO) * other.radius / (GAME_BLOB_RATIO);
      this.radius = Math.sqrt(sum / PI);
      return true;
    } else {
      return false;
    }
  };

  this.eatsPlayer = (other) => {
    const distance = p5.Vector.dist(this.position, other.position);

    if (distance < this.radius && this.radius > other.radius) {
      const sum = PI * this.radius * this.radius + PI * other.radius / USER_BLOB_RATIO * other.radius / USER_BLOB_RATIO;
      this.radius = Math.sqrt(sum / PI);
      return true;
    } else {
      return false;
    }
  };

  this.constrain = () => {
    this.position.x = constrain(this.position.x, -MAX_WIDTH, MAX_WIDTH);
    this.position.y = constrain(this.position.y, -MAX_HEIGHT, MAX_HEIGHT);
  };

  this.show = () => {
    fill(COLOUR_WHITE);
    ellipse(this.position.x, this.position.y, this.radius * 2, this.radius * 2);
  };
}

module.exports = Blob;
