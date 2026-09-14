// Dựng bàn cờ 10x10
const board = document.getElementById('board');
if (board) {
    for (let i = 0; i < 100; i++) {
        const cell = document.createElement('div');
        cell.classList.add('cell');
        board.appendChild(cell);
    }
}

// Chuyển màn hình từ Menu -> Bàn cờ
document.getElementById('start-btn').addEventListener('click', () => {
    document.getElementById('menu-screen').classList.add('hidden');
    document.getElementById('game-screen').classList.remove('hidden');
});

const pauseModal = document.getElementById('pause-modal');
const winModal = document.getElementById('win-modal');

// Bấm DỪNG GAME -> Hiện khung TẠM DỪNG
document.getElementById('pause-btn').addEventListener('click', () => {
    pauseModal.classList.remove('hidden');
});

// Nút TIẾP TỤC -> Ẩn khung Dừng game
document.getElementById('resume-btn').addEventListener('click', () => {
    pauseModal.classList.add('hidden');
});

// Nút XEM LẠI TRẬN ĐẤU -> Ẩn khung Thắng cuộc
document.getElementById('replay-btn').addEventListener('click', () => {
    winModal.classList.add('hidden');
});

// Trở về Menu chính từ các Modal
document.getElementById('quit-home-btn').addEventListener('click', goHome);
document.getElementById('win-home-btn').addEventListener('click', goHome);

function goHome() {
    pauseModal.classList.add('hidden');
    winModal.classList.add('hidden');
    document.getElementById('game-screen').classList.add('hidden');
    document.getElementById('menu-screen').classList.remove('hidden');
}