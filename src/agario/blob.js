function Blob(x, y, r, id) {
  this.pos = createVector(x, y, 0);
  this.r = r;
  this.vel = createVector(0, 0, 0);

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
      const sum = PI * this.r * this.r + PI * other.r/(1.5) * other.r/(1.5);
      this.r = sqrt(sum / PI);
      return true;
    } else {
      return false;
    }
  };

  this.eatsPlayer = (other) => {
    console.log('this' ,this);
    console.log('other', other);
    const d = p5.Vector.dist(this.pos, other.pos);
    console.log('Eaten');

    if (d < this.r) {
      // const sum = PI * this.r * this.r + PI * other.r/2 * other.r/2;
      this.r += other.r;
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
  };

  this.showUserBlob = () => {
    fill(0, 0, 255);
    ellipse(this.pos.x, this.pos.y, this.r * 2, r * 2);

    fill(255);
    textAlign(CENTER);
    textSize(4);
    text(this.id, this.pos.x, this.pos.y + this.r);
  }
}
