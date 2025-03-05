function dijkstra(start) {
    // Khởi tạo khoảng cách và node trước đó
    let distances = {};
    let prev = {};
    let queue = new Set(cy.nodes().map(node => node.id()));

    // Đặt khoảng cách ban đầu là vô cực, trừ node bắt đầu
    cy.nodes().forEach(node => distances[node.id()] = Infinity);
    distances[start] = 0;

    while (queue.size > 0) {
        // Tìm node có khoảng cách nhỏ nhất trong queue
        let minNode = [...queue].reduce((a, b) => distances[a] < distances[b] ? a : b);
        queue.delete(minNode);
        cy.getElementById(minNode).style('background-color', 'green'); // Đánh dấu node đã thăm

        // Duyệt qua các cạnh kết nối với node hiện tại
        let edges = cy.getElementById(minNode).connectedEdges();
        edges.forEach(edge => {
            // Xác định node lân cận
            let neighbor = edge.target().id() === minNode ? edge.source().id() : edge.target().id();
            if (queue.has(neighbor)) {
                let weight = edge.data('weight'); // Lấy trọng số của cạnh
                let alt = distances[minNode] + weight; // Tính khoảng cách mới
                if (alt < distances[neighbor]) {
                    distances[neighbor] = alt; // Cập nhật khoảng cách
                    prev[neighbor] = minNode;  // Lưu node trước đó
                    cy.getElementById(neighbor).style('background-color', 'yellow'); // Đánh dấu node được cập nhật
                }
            }
        });
    }
    return { distances, prev }; // Trả về kết quả nếu cần
}
document.getElementById('dijkstra-btn').addEventListener('click', function() {
    var start = document.getElementById('dijkstra-start').value;
    if (start && cy.getElementById(start).length) {
        dijkstra(start);
    }
});