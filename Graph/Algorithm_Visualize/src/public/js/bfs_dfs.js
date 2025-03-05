function* dfs(start) {
    let stack = [start]; 
    let visited = new Set();
    let outputList = document.getElementById('dfs-output');  
    outputList.innerHTML = ""; // Xóa danh sách cũ khi chạy lại

    while (stack.length > 0) {
        let current = stack.pop();
        if (!visited.has(current)) {
            visited.add(current);
            yield current; 
            cy.getElementById(current).style('background-color', 'green');

            // 📝 Thêm node vào danh sách DFS
            let listItem = document.createElement("li");
            listItem.textContent = current;
            listItem.style.display = "inline";
            listItem.style.margin = "1px 5px"
            outputList.appendChild(listItem);

            let neighbors = cy.getElementById(current).neighborhood().nodes();
            neighbors.forEach(neighbor => {
                let neighborId = neighbor.id();
                if (!visited.has(neighborId)) {
                    stack.push(neighborId);
                    if (!stack.includes(neighborId)) { 
                        cy.getElementById(neighborId).style('background-color', 'yellow');
                    }
                }
            });
        }
    }
}


// Xử lý sự kiện khi nhấn nút "Chạy DFS"
document.getElementById('dfs-btn').addEventListener('click', function() {
    var start = document.getElementById('node-start').value; // Lấy node bắt đầu từ input
    if (start && cy.getElementById(start).length > 0) {
        let dfsGen = dfs(start); // Khởi tạo generator DFS
        function step() {
            let result = dfsGen.next();
            if (!result.done) {
                setTimeout(step, 1000); // Chờ 1 giây giữa các bước để visualize
            }
        }
        step(); // Bắt đầu quá trình duyệt
    } else {
        alert("Vui lòng nhập node bắt đầu hợp lệ!");
    }
});