// Game State
let gameState = {
    board: [],
    currentPlayer: 1, // 1 for black (x), 2 for white (o)
    player1Name: 'Player 1',
    player2Name: 'Player 2',
    scores: { black: 2, white: 2 },
    gameActive: false,
    validMoves: []
};

// Initialize game
function initGame() {
    // Create 8x8 board
    gameState.board = Array(8).fill(null).map(() => Array(8).fill(0));
    
    // Set initial pieces
    gameState.board[3][3] = 1; // Black
    gameState.board[3][4] = 2; // White
    gameState.board[4][3] = 2; // White
    gameState.board[4][4] = 1; // Black
    
    gameState.currentPlayer = 1;
    gameState.scores = { black: 2, white: 2 };
    gameState.gameActive = true;
    
    renderBoard();
    updateScores();
    updateTurnIndicator();
    calculateValidMoves();
}

// Render the game board
function renderBoard() {
    const boardElement = document.getElementById('gameBoard');
    boardElement.innerHTML = '';
    
    for (let row = 0; row < 8; row++) {
        for (let col = 0; col < 8; col++) {
            const cell = document.createElement('div');
            cell.className = 'cell';
            cell.dataset.row = row;
            cell.dataset.col = col;
            cell.onclick = () => handleCellClick(row, col);
            
            if (gameState.board[row][col] === 1) {
                const disc = document.createElement('div');
                disc.className = 'disc black';
                disc.textContent = '⚫';
                cell.appendChild(disc);
            } else if (gameState.board[row][col] === 2) {
                const disc = document.createElement('div');
                disc.className = 'disc white';
                disc.textContent = '⚪';
                cell.appendChild(disc);
            }
            
            // Highlight valid moves
            if (isValidMove(row, col, gameState.currentPlayer)) {
                cell.classList.add('valid-move');
            }
            
            boardElement.appendChild(cell);
        }
    }
}

// Handle cell click
function handleCellClick(row, col) {
    if (!gameState.gameActive) return;
    
    if (isValidMove(row, col, gameState.currentPlayer)) {
        makeMove(row, col, gameState.currentPlayer);
        
        // Switch player
        gameState.currentPlayer = gameState.currentPlayer === 1 ? 2 : 1;
        
        // Check if next player has valid moves
        calculateValidMoves();
        
        if (gameState.validMoves.length === 0) {
            // Current player has no moves, switch back
            gameState.currentPlayer = gameState.currentPlayer === 1 ? 2 : 1;
            calculateValidMoves();
            
            if (gameState.validMoves.length === 0) {
                // No one has moves, game over
                endGame();
                return;
            } else {
                showMessage(`${getCurrentPlayerName()} has no valid moves. Passing turn.`);
            }
        }
        
        renderBoard();
        updateScores();
        updateTurnIndicator();
        
        // Check if board is full
        if (isBoardFull()) {
            endGame();
        }
    }
}

// Check if a move is valid
function isValidMove(row, col, player) {
    if (gameState.board[row][col] !== 0) return false;
    
    const opponent = player === 1 ? 2 : 1;
    const directions = [
        [-1, -1], [-1, 0], [-1, 1],
        [0, -1],           [0, 1],
        [1, -1],  [1, 0],  [1, 1]
    ];
    
    for (let [dx, dy] of directions) {
        let newRow = row + dx;
        let newCol = col + dy;
        let foundOpponent = false;
        
        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (gameState.board[newRow][newCol] === 0) break;
            
            if (gameState.board[newRow][newCol] === opponent) {
                foundOpponent = true;
            } else if (gameState.board[newRow][newCol] === player) {
                if (foundOpponent) return true;
                break;
            }
            
            newRow += dx;
            newCol += dy;
        }
    }
    
    return false;
}

// Make a move
function makeMove(row, col, player) {
    gameState.board[row][col] = player;
    
    const opponent = player === 1 ? 2 : 1;
    const directions = [
        [-1, -1], [-1, 0], [-1, 1],
        [0, -1],           [0, 1],
        [1, -1],  [1, 0],  [1, 1]
    ];
    
    for (let [dx, dy] of directions) {
        let toFlip = [];
        let newRow = row + dx;
        let newCol = col + dy;
        
        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (gameState.board[newRow][newCol] === 0) break;
            
            if (gameState.board[newRow][newCol] === opponent) {
                toFlip.push([newRow, newCol]);
            } else if (gameState.board[newRow][newCol] === player) {
                // Flip all pieces in between
                for (let [flipRow, flipCol] of toFlip) {
                    gameState.board[flipRow][flipCol] = player;
                    animateFlip(flipRow, flipCol);
                }
                break;
            }
            
            newRow += dx;
            newCol += dy;
        }
    }
}

// Animate disc flip
function animateFlip(row, col) {
    const cell = document.querySelector(`[data-row="${row}"][data-col="${col}"]`);
    if (cell) {
        const disc = cell.querySelector('.disc');
        if (disc) {
            disc.classList.add('flipping');
            setTimeout(() => {
                disc.classList.remove('flipping');
            }, 600);
        }
    }
}

// Calculate valid moves for current player
function calculateValidMoves() {
    gameState.validMoves = [];
    for (let row = 0; row < 8; row++) {
        for (let col = 0; col < 8; col++) {
            if (isValidMove(row, col, gameState.currentPlayer)) {
                gameState.validMoves.push([row, col]);
            }
        }
    }
}

// Update scores
function updateScores() {
    let blackCount = 0;
    let whiteCount = 0;
    
    for (let row = 0; row < 8; row++) {
        for (let col = 0; col < 8; col++) {
            if (gameState.board[row][col] === 1) blackCount++;
            else if (gameState.board[row][col] === 2) whiteCount++;
        }
    }
    
    gameState.scores.black = blackCount;
    gameState.scores.white = whiteCount;
    
    document.getElementById('player1Score').textContent = blackCount;
    document.getElementById('player2Score').textContent = whiteCount;
}

// Update turn indicator
function updateTurnIndicator() {
    const turnIndicator = document.getElementById('currentTurn');
    const player1Card = document.getElementById('player1Card');
    const player2Card = document.getElementById('player2Card');
    
    if (gameState.currentPlayer === 1) {
        turnIndicator.textContent = `${gameState.player1Name}'s Turn ⚫`;
        player1Card.classList.add('active');
        player2Card.classList.remove('active');
    } else {
        turnIndicator.textContent = `${gameState.player2Name}'s Turn ⚪`;
        player2Card.classList.add('active');
        player1Card.classList.remove('active');
    }
}

// Check if board is full
function isBoardFull() {
    for (let row = 0; row < 8; row++) {
        for (let col = 0; col < 8; col++) {
            if (gameState.board[row][col] === 0) return false;
        }
    }
    return true;
}

// Get current player name
function getCurrentPlayerName() {
    return gameState.currentPlayer === 1 ? gameState.player1Name : gameState.player2Name;
}

// Pass move
function passMove() {
    if (!gameState.gameActive) return;
    
    if (gameState.validMoves.length > 0) {
        showMessage('You have valid moves available!');
        return;
    }
    
    gameState.currentPlayer = gameState.currentPlayer === 1 ? 2 : 1;
    calculateValidMoves();
    
    if (gameState.validMoves.length === 0) {
        endGame();
        return;
    }
    
    renderBoard();
    updateTurnIndicator();
    showMessage(`${getCurrentPlayerName()} passed. ${getCurrentPlayerName()}'s turn now.`);
}

// End game
function endGame() {
    gameState.gameActive = false;
    
    const modal = document.getElementById('gameOverModal');
    const winnerMessage = document.getElementById('winnerMessage');
    
    document.getElementById('finalPlayer1Name').textContent = gameState.player1Name;
    document.getElementById('finalPlayer2Name').textContent = gameState.player2Name;
    document.getElementById('finalPlayer1Score').textContent = gameState.scores.black;
    document.getElementById('finalPlayer2Score').textContent = gameState.scores.white;
    
    if (gameState.scores.black > gameState.scores.white) {
        winnerMessage.innerHTML = `🏆 ${gameState.player1Name} Wins! 🏆`;
    } else if (gameState.scores.white > gameState.scores.black) {
        winnerMessage.innerHTML = `🏆 ${gameState.player2Name} Wins! 🏆`;
    } else {
        winnerMessage.innerHTML = `🤝 It's a Tie! 🤝`;
    }
    
    modal.classList.add('active');
}

// Show message
function showMessage(message) {
    // Simple alert for now, you can enhance this with a custom notification
    const turnIndicator = document.getElementById('turnIndicator');
    const originalText = turnIndicator.querySelector('#currentTurn').textContent;
    turnIndicator.querySelector('#currentTurn').textContent = message;
    
    setTimeout(() => {
        turnIndicator.querySelector('#currentTurn').textContent = originalText;
    }, 2000);
}

// Navigation functions
function showSection(section) {
    // Hide all screens
    document.querySelectorAll('.screen').forEach(screen => {
        screen.classList.remove('active');
    });
    
    // Show selected screen
    if (section === 'creator') {
        document.getElementById('creatorScreen').classList.add('active');
    } else if (section === 'rules') {
        document.getElementById('rulesScreen').classList.add('active');
    } else if (section === 'setup') {
        document.getElementById('setupScreen').classList.add('active');
    }
}

function goBack() {
    document.querySelectorAll('.screen').forEach(screen => {
        screen.classList.remove('active');
    });
    document.getElementById('welcomeScreen').classList.add('active');
}

function startGame() {
    const player1Input = document.getElementById('player1').value.trim();
    const player2Input = document.getElementById('player2').value.trim();
    
    if (!player1Input || !player2Input) {
        alert('Please enter names for both players!');
        return;
    }
    
    gameState.player1Name = player1Input;
    gameState.player2Name = player2Input;
    
    document.getElementById('player1Name').textContent = player1Input;
    document.getElementById('player2Name').textContent = player2Input;
    
    // Hide all screens and show game screen
    document.querySelectorAll('.screen').forEach(screen => {
        screen.classList.remove('active');
    });
    document.getElementById('gameScreen').classList.add('active');
    
    // Initialize the game
    initGame();
}

function restartGame() {
    // Close modal if open
    document.getElementById('gameOverModal').classList.remove('active');
    
    // Reset and start new game
    initGame();
}

function exitGame() {
    // Close modal if open
    document.getElementById('gameOverModal').classList.remove('active');
    
    // Go back to welcome screen
    document.querySelectorAll('.screen').forEach(screen => {
        screen.classList.remove('active');
    });
    document.getElementById('welcomeScreen').classList.add('active');
    
    // Clear player names
    document.getElementById('player1').value = '';
    document.getElementById('player2').value = '';
    
    gameState.gameActive = false;
}

// Initialize on page load
document.addEventListener('DOMContentLoaded', () => {
    // Show welcome screen by default
    document.getElementById('welcomeScreen').classList.add('active');
});
