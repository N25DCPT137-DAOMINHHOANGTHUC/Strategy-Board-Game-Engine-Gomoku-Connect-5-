document.addEventListener('DOMContentLoaded', () => {
    const board = document.getElementById('board');
    const modeOptions = document.querySelectorAll('.mode-option');
    const p2Icon = document.getElementById('p2-icon');
    const p2Name = document.getElementById('p2-name');

    let currentMode = 'pvp';  // Mặc định là PvP ('pvp' hoặc 'pvb')
    let currentPlayer = 'X'; 
    let isGameOver = false;

    // 1. XỬ LÝ CHỌN CHẾ ĐỘ CHƠI Ở MENU
    modeOptions.forEach(option => {
        option.addEventListener('click', () => {
            modeOptions.forEach(opt => opt.classList.remove('active'));
            option.classList.add('active');
            
            // Ưu tiên lấy từ data-mode, nếu không có sẽ kiểm tra theo chữ BOT
            if (option.dataset.mode) {
                currentMode = option.dataset.mode;
            } else if (option.textContent.includes('BOT')) {
                currentMode = 'pvb';
            } else {
                currentMode = 'pvp';
            }
        });
    });

    // 2. CHUYỂN MÀN HÌNH & KHỞI TẠO BÀN CỜ (Đã gộp localStorage chuẩn)
    const startBtn = document.getElementById('start-btn');
    if (startBtn) {
        startBtn.addEventListener('click', () => {
            // LƯU CHẾ ĐỘ CHƠI VÀO BỘ NHỚ TRÌNH DUYỆT
            localStorage.setItem('gameMode', currentMode);

            // Cập nhật giao diện Player 2 ngay trên màn hình bàn cờ
            if (currentMode === 'pvb') {
                if (p2Icon) p2Icon.className = 'fa-solid fa-robot player-icon';
                if (p2Name) p2Name.textContent = 'BOT';
            } else {
                if (p2Icon) p2Icon.className = 'fa-solid fa-user player-icon';
                if (p2Name) p2Name.textContent = 'Player 2';
            }

            document.getElementById('menu-screen').classList.add('hidden');
            document.getElementById('game-screen').classList.remove('hidden');

            currentPlayer = 'X';
            isGameOver = false;
            initBoard();
            updateTurnBadge();
        });
    }

    // 3. DỰNG BÀN CỜ VÀ XỬ LÝ LƯỢT ĐÁNH
    function initBoard() {
        if (!board) return;
        board.innerHTML = '';
        for (let i = 0; i < 100; i++) {
            const cell = document.createElement('div');
            cell.classList.add('cell');

            cell.addEventListener('click', () => {
                if (cell.textContent !== '' || isGameOver) return;

                // Nếu đang ở chế độ PLAYER vs BOT và đến lượt O -> Không cho người dùng bấm đánh
                if (currentMode === 'pvb' && currentPlayer === 'O') {
                    return; 
                }

                // Người chơi đánh quân X
                if (currentPlayer === 'X') {
                    cell.textContent = '✖';
                    cell.classList.add('symbol-x');
                    currentPlayer = 'O'; // Đổi lượt sang O (Máy)
                    updateTurnBadge();
                } 
                // Người chơi đánh quân O (Chỉ hoạt động ở chế độ PvP)
                else if (currentMode === 'pvp') {
                    cell.textContent = '⭕';
                    cell.classList.add('symbol-o');
                    currentPlayer = 'X'; // Đổi lượt sang X
                    updateTurnBadge();
                }
            });

            board.appendChild(cell);
        }
    }

    // 4. HÀM CẬP NHẬT BADGE "➔ ĐI TIẾP"
    function updateTurnBadge() {
        const playerBoxes = document.querySelectorAll('.player-box');
        if (playerBoxes.length >= 2) {
            if (currentPlayer === 'X') {
                playerBoxes[0].classList.add('active');
                playerBoxes[1].classList.remove('active');
            } else {
                playerBoxes[1].classList.add('active');
                playerBoxes[0].classList.remove('active');
            }
        }
    }

    // 5. XỬ LÝ POPUP MODAL
    const pauseModal = document.getElementById('pause-modal');
    const winModal = document.getElementById('win-modal');

    const pauseBtn = document.getElementById('pause-btn');
    const resumeBtn = document.getElementById('resume-btn');
    const replayBtn = document.getElementById('replay-btn');
    const quitHomeBtn = document.getElementById('quit-home-btn');
    const winHomeBtn = document.getElementById('win-home-btn');

    if (pauseBtn) pauseBtn.addEventListener('click', () => pauseModal.classList.remove('hidden'));
    if (resumeBtn) resumeBtn.addEventListener('click', () => pauseModal.classList.add('hidden'));
    if (replayBtn) replayBtn.addEventListener('click', () => winModal.classList.add('hidden'));

    if (quitHomeBtn) quitHomeBtn.addEventListener('click', goHome);
    if (winHomeBtn) winHomeBtn.addEventListener('click', goHome);

    function goHome() {
        if (pauseModal) pauseModal.classList.add('hidden');
        if (winModal) winModal.classList.add('hidden');
        document.getElementById('game-screen').classList.add('hidden');
        document.getElementById('menu-screen').classList.remove('hidden');
    }
});