// 引入必要的命名空间
using Microsoft.AspNetCore.Mvc;
using PartyAPI.Models; 

// 创建 Web 应用程序构建器和应用程序实例
var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

// 初始化派对列表数据（模拟数据库）
var parties = new List<Party>
{
    new Party { Id = 1, Topic = "Birthday Party", Location = "New York", Time = DateTime.Now.AddDays(10) },
    new Party { Id = 2, Topic = "Wedding Anniversary", Location = "Los Angeles", Time = DateTime.Now.AddDays(20) }
};

// GET 请求：获取所有派对信息
// http://localhost:5000/Party/All
app.MapGet("/Party/All", () => Results.Ok(parties));

// GET 请求：根据ID获取特定派对信息
// http://localhost:5000/Party/1
app.MapGet("/Party/{id}", (int id) =>
{
    var party = parties.FirstOrDefault(p => p.Id == id);
    return party == null ? Results.NotFound() : Results.Ok(party);
});

// POST 请求：创建新的派对
// http://localhost:5000/Party
app.MapPost("/Party", (Party party) =>
{
    // 自动生成新的ID（获取当前最大ID值+1）
    party.Id = parties.Any() ? parties.Max(p => p.Id) + 1 : 1;
    parties.Add(party);
    // 返回201 Created状态码和新创建的资源路径
    return Results.Created($"/Party/{party.Id}", party);
});

// PUT 请求：更新指定ID的派对信息
/*
* http://localhost:5000/Party/1?topic=Updated%20Party&location=San%20Francisco&time=2023-12-31T20:00:00
*/
app.MapPut("/Party/{id}", (int id, [FromQuery] string? topic, [FromQuery] string? location, [FromQuery] DateTime? time) =>
{
    // 查找指定 ID 的派对信息
    var party = parties.FirstOrDefault(p => p.Id == id);
    if (party == null) return Results.NotFound();

    // 更新派对信息（仅更新非空字段）
    if (!string.IsNullOrEmpty(topic)) party.Topic = topic;
    if (!string.IsNullOrEmpty(location)) party.Location = location;
    if (time.HasValue) party.Time = time.Value;

    return Results.NoContent(); // 返回 HTTP 204 状态码
});

// DELETE 请求：删除指定ID的派对
// http://localhost:5000/Party/1
app.MapDelete("/Party/{id}", (int id) =>
{
    var party = parties.FirstOrDefault(p => p.Id == id);
    if (party == null) return Results.NotFound();

    parties.Remove(party);
    return Results.NoContent();
});

// 启动应用程序
app.Run();