const { generateUUID, updateHighScore, updateScore } = require('../helpers');

describe('helpers', () => {
    test('generateUUID', () => {
        const uuidRegex = new RegExp(/^[0-9A-F]{8}-[0-9A-F]{4}-[4][0-9A-F]{3}-[89AB][0-9A-F]{3}-[0-9A-F]{12}$/i);
        const uuid = generateUUID();
        expect(uuidRegex.test(uuid)).toBeTruthy();
    });

    test('updateHighScore', () => {
        const highscoreDivId = 'highscore';
        const getElementById = jest.fn(() => ({
            innerHTML: '',
        }));

        document.getElementById = getElementById;
        const highScore = 125;
        updateHighScore(highScore);

        expect(getElementById).toHaveBeenCalledWith(highscoreDivId);
    });

    test('updateScore - should call updateHighScore if current score is greater than the highscore', () => {
        const highscoreDivId = 'highscore';
        const scoreDivId = 'score';
        const getElementById = jest.fn(() => ({
            innerHTML: 12,
        }));

        document.getElementById = getElementById;
        const score = 125;
        updateScore(score);

        expect(getElementById.mock.calls[0][0]).toEqual(scoreDivId);
        expect(getElementById.mock.calls[1][0]).toEqual(highscoreDivId);
        expect(getElementById.mock.calls[2][0]).toEqual(highscoreDivId);

        expect(getElementById).toHaveBeenCalledTimes(3);
    });

    test('updateScore - should not call updateHighScore if current score is not greater than the highscore', () => {
        const scoreDivId = 'score';
        const highScoreDivId = 'highscore';
        const getElementById = jest.fn(() => ({
            innerHTML: 120,
        }));

        document.getElementById = getElementById;
        const score = 5;
        updateScore(score);

        expect(getElementById.mock.calls[0][0]).toEqual(scoreDivId);
        expect(getElementById.mock.calls[1][0]).toEqual(highScoreDivId);
        expect(getElementById).toHaveBeenCalledTimes(2);
    });
});
