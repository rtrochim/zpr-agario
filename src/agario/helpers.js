const uuidPattern = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx';

function generateUUID () {
    let currentDate = new Date().getTime();

    const uuid = uuidPattern.replace(/[xy]/g, (c) => {
        const r = (currentDate + Math.random() * 16) % 16 | 0;
        currentDate = Math.floor(currentDate / 16);
        return (c === 'x' ? r : (r & 0x3 |0x8)).toString(16);
    });

    return uuid;
}

function updateHighScore (highScore) {
    document.getElementById('highscore').innerHTML = highScore;
}

function updateScore (score) {
    document.getElementById('score').innerHTML = score;
    const highScore = document.getElementById('highscore').innerHTML;

    if (parseInt(score) > parseInt(highScore)) {
        updateHighScore(score);
    }
}

module.exports = {
    generateUUID,
    updateHighScore,
    updateScore,
};
