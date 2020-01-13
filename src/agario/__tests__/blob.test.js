const Blob = require('../blob');

window.createVector = jest.fn((x, y) => ({ x, y }));
window.constrain = jest.fn((x, y) => ({ x, y }));
window.ellipse = jest.fn((x, y) => ({ x, y }));
window.fill = jest.fn((x, y) => ({ x, y }));

window.mouseX = 0;
window.mouseY = 0;

window.width = 900;
window.height = 1400;

describe('Blob', () => {
    beforeEach(() => {
        window.createVector.mockClear();
        window.constrain.mockClear();
        window.ellipse.mockClear();
        window.fill.mockClear();
    });

   test('creates a new blob', () => {
       const x = 12;
       const y = 15;
       const blob = new Blob(x, y, 20);

       expect(blob.position).toHaveProperty('x', x);
       expect(blob.position).toHaveProperty('y', y);
   });

   test('updates blob position with correct parameters', () => {
       const add = jest.fn();
       const lerp = jest.fn();
       const limit = jest.fn();

        window.createVector = jest.fn((x, y) => ({
            add,
            lerp,
            limit,
            x,
            y,
        }));

       const x = 12;
       const y = 15;
       const blob = new Blob(x, y, 20);

        blob.update();
        expect(add).toHaveBeenCalledWith(blob.velocity);
        expect(lerp).toHaveBeenCalled();
        expect(limit).toHaveBeenCalledWith(3 - (blob.radius / 100));
   });
});