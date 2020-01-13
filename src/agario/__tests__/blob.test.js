const Blob = require('../blob');

const MAX_WIDTH = 900;
const MAX_HEIGHT = 1400;
const COLOUR_WHITE = 255;

window.createVector = jest.fn((x, y) => ({ x, y }));
window.ellipse = jest.fn((x, y) => ({ x, y }));
window.fill = jest.fn((x, y) => ({ x, y }));

window.mouseX = 0;
window.mouseY = 0;

window.width = 900;
window.height = 1400;
window.MAX_WIDTH = MAX_WIDTH;
window.MAX_HEIGHT = MAX_HEIGHT;

window.PI = 3.14159265;

describe('Blob', () => {
    beforeEach(() => {
        window.createVector.mockClear();
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

   test('eats a game blob and increments blob\'s radius', () => {
       const x = 12;
       const y = 15;
       const radius = 20;
       const mainBlob = new Blob(x, y, radius);
       const gameBlob = new Blob(x, y, 5);
       const dist = jest.fn(() => 5);

       window.p5 = {
           Vector: {
               dist,
           },
       };

       const result = mainBlob.eats(gameBlob);
       expect(mainBlob.radius).toBeGreaterThan(radius);
       expect(result).toBeTruthy();
   });

   test('does not eat the game blob if they are too far away from each other', () => {
       const x = 12;
       const y = 15;
       const radius = 20;
       const mainBlob = new Blob(x, y, radius);
       const gameBlob = new Blob(x, y, 5);
       const dist = jest.fn(() => 50);

       window.p5 = {
           Vector: {
               dist,
           },
       };

       const result = mainBlob.eats(gameBlob);
       expect(mainBlob.radius).toEqual(radius);
       expect(result).toBeFalsy();
   });

    test('eats a user blob and increments blob\'s radius', () => {
        const x = 12;
        const y = 15;
        const radius = 20;
        const mainBlob = new Blob(x, y, radius);
        const smallBlob = new Blob(x, y, 5);
        const dist = jest.fn(() => 5);

        window.p5 = {
            Vector: {
                dist,
            },
        };

        const result = mainBlob.eatsPlayer(smallBlob);
        expect(mainBlob.radius).toBeGreaterThan(radius);
        expect(result).toBeTruthy();
    });

    test('does not eat the user blob if they are too far away from each other or the second blob is bigger', () => {
        const x = 12;
        const y = 15;
        const radius = 20;
        const mainBlob = new Blob(x, y, radius);
        const smallBlob = new Blob(x, y, 5);
        const largeBlob = new Blob(x, y, 50);
        const dist = jest.fn(() => 50);

        window.p5 = {
            Vector: {
                dist,
            },
        };

        const smallBlobResult = mainBlob.eatsPlayer(smallBlob);
        expect(mainBlob.radius).toEqual(radius);
        expect(smallBlobResult).toBeFalsy();

        const largeBlobResult = mainBlob.eatsPlayer(largeBlob);
        expect(mainBlob.radius).toEqual(radius);
        expect(largeBlobResult).toBeFalsy();
    });

    test('constrain', () => {
        const x = 12;
        const y = 15;
        const radius = 20;
        const mainBlob = new Blob(x, y, radius);
        const constrain = jest.fn();
        window.constrain = constrain;
        mainBlob.constrain();

        expect(constrain.mock.calls[0][0]).toEqual(x);
        expect(constrain.mock.calls[0][1]).toEqual(-MAX_WIDTH);
        expect(constrain.mock.calls[0][2]).toEqual(MAX_WIDTH);

        expect(constrain.mock.calls[1][0]).toEqual(y);
        expect(constrain.mock.calls[1][1]).toEqual(-MAX_HEIGHT);
        expect(constrain.mock.calls[1][2]).toEqual(MAX_HEIGHT);
    });

    test('show', () => {
        const x = 12;
        const y = 15;
        const radius = 20;
        const blob = new Blob(x, y, radius);
        blob.show();
        expect(window.fill).toHaveBeenCalledWith(COLOUR_WHITE);
        expect(window.ellipse).toHaveBeenCalledWith(blob.position.x, blob.position.y, blob.radius * 2, blob.radius * 2);
    });
});
