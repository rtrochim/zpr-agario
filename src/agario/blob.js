function Blob(x, y, radius) {
  this.position = createVector(x, y, 0);
  this.radius = radius;
  this.velocity = createVector(0, 0, 0);

  this.update = () => {
    const newVelocity = createVector((mouseX - width / 2), (mouseY - height / 2));
    newVelocity.limit(3 - (this.radius / 100));
    this.velocity.lerp(newVelocity, 0.2);
    this.position.add(this.velocity);
  };

  this.eats = (other) => {
    const distance = p5.Vector.dist(this.position, other.position);
    if (distance < this.radius + other.radius) {
      const sum = PI * this.radius * this.radius + PI * other.radius / (1.5) * other.radius / (1.5);
      this.radius = sqrt(sum / PI);
      return true;
    } else {
      return false;
    }
  };

  this.eatsPlayer = (other) => {
    const distance = p5.Vector.dist(this.position, other.position);

    if (distance < this.radius && this.radius > other.radius) {
      const sum = PI * this.radius * this.radius + PI * other.radius / 2 * other.radius / 2;
      this.radius = sqrt(sum / PI);
      return true;
    } else {
      return false;
    }
  };

  this.constrain = () => {
    blob.position.x = constrain(blob.position.x, -1400, 1400);
    blob.position.y = constrain(blob.position.y, -900, 900);
  };

  this.show = () => {
    fill(255);
    ellipse(this.position.x, this.position.y, this.radius * 2, this.radius * 2);
  };
}
