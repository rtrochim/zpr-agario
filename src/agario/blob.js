function Blob(x, y, r) {
  this.pos = createVector(x, y);
  this.r = r;
  this.vel = createVector(0, 0);

  this.update = () => {
    const newvel = createVector(mouseX - width / 2, mouseY - height / 2);
    newvel.div(50);
    newvel.setMag(3);
    newvel.limit(3);
    this.vel.lerp(newvel, 0.2);
    this.pos.add(this.vel);
  };

  this.eats = (other) => {
    const d = p5.Vector.dist(this.pos, other.pos);
    if (d < this.r + other.r) {
      const sum = PI * this.r * this.r + PI * other.r * other.r;
      this.r = sqrt(sum / PI);
      //this.r += other.r;
      return true;
    } else {
      return false;
    }
  };

  this.constrain = () => {
    blob.pos.x = constrain(0, -1400, 1400);
    blob.pos.y = constrain(0, -900, 900);
  };

  this.show = () => {
    fill(255);
    ellipse(this.pos.x, this.pos.y, this.r * 2, this.r * 2);
  }
}
