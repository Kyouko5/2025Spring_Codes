using Microsoft.AspNetCore.Mvc;
using RSVPSystem.Models;
using System.Diagnostics;

namespace RSVPSystem.Controllers
{
    public class HomeController : Controller
    {
        // 模拟数据库，使用静态列表存储派对和参与者信息
        private static readonly List<Party> Parties = new List<Party>
        {
            new Party { Name = "Party1", Location = "L1", Date = new DateTime(2020, 12, 21) },
            new Party { Name = "Party2", Location = "L2", Date = new DateTime(2020, 12, 22) },
            new Party { Name = "Party3", Location = "L3", Date = new DateTime(2020, 12, 25) }
        };

        private static readonly List<Attendee> Attendees = new List<Attendee>
        {
            new Attendee { Id = 1, Name = "Alice Jones", Email = "alice@example.com", Phone = "555-123-5678", Parties = new List<string> { "Party1", "Party2" } },
            new Attendee { Id = 2, Name = "Peter Davies", Email = "peter@example.com", Phone = "555-456-7890", Parties = new List<string> { "Party1" } },
            new Attendee { Id = 3, Name = "Dora Francis", Email = "dora@example.com", Phone = "555-456-1234", Parties = new List<string> { "Party1" } },
            new Attendee { Id = 4, Name = "Bob Smith", Email = "bob@example.com", Phone = "555-123-1234", Parties = new List<string> { "Party1" } }
        };

        public IActionResult Index()
        {
            // 显示派对列表
            return View(Parties);
        }

        // 显示注册页面
        [HttpGet]
        public IActionResult Register(string partyName)
        {
            ViewBag.PartyName = partyName;
            return View();
        }

        // 处理注册表单提交
        [HttpPost]
        public IActionResult Register(Attendee attendee, string partyName)
        {
            if (ModelState.IsValid)
            {
                attendee.Id = Attendees.Count + 1;
                attendee.Parties.Add(partyName);
                Attendees.Add(attendee);
                return RedirectToAction("ShowAttendees", new { partyName = partyName });
            }
            ViewBag.PartyName = partyName;
            return View(attendee);
        }

        // 显示参与者信息
        public IActionResult ShowAttendees(string partyName)
        {
            var attendees = Attendees.Where(a => a.Parties.Contains(partyName)).ToList();
            ViewBag.PartyName = partyName;
            return View(attendees);
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}