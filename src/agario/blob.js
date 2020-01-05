function Blob(x, y, r) {
  this.pos = createVector(x, y);
  this.r = r;
  this.vel = createVector(0, 0);

  this.update = () => {
    const newvel = createVector((mouseX - width / 2), (mouseY - height / 2));
    // newvel.div(5);
    // newvel.setMag(3/);
    newvel.limit(3 - (this.r/100));
    this.vel.lerp(newvel, 0.2);
    this.pos.add(this.vel);
  };

  this.eats = (other) => {
    const d = p5.Vector.dist(this.pos, other.pos);
    if (d < this.r + other.r) {
      const sum = PI * this.r * this.r + PI * other.r/2 * other.r/2;
      this.r = sqrt(sum / PI);
      return true;
    } else {
      return false;
    }
  };

  this.constrain = () => {
    blob.pos.x = constrain(blob.pos.x, -1400, 1400);
    blob.pos.y = constrain(blob.pos.y, -900, 900);
  };

  this.show = () => {
    fill(255);
    ellipse(this.pos.x, this.pos.y, this.r * 2, this.r * 2);
  }
}
