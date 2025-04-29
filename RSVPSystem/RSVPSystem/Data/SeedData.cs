using Microsoft.EntityFrameworkCore;
using RSVPSystem.Models;

namespace RSVPSystem.Data
{
    public static class SeedData
    {
        public static void Initialize(IServiceProvider serviceProvider)
        {
            using var context = new ApplicationDbContext(
                serviceProvider.GetRequiredService<DbContextOptions<ApplicationDbContext>>());

            // Look for any attendees or parties
            if (context.Attendees.Any() || context.Parties.Any())
            {
                return;   // DB has been seeded
            }

            // Add sample attendees
            var attendees = new List<Attendee>
            {
                new Attendee { Name = "张三", Email = "zhangsan@example.com", Phone = "13812345678" },
                new Attendee { Name = "李四", Email = "lisi@example.com", Phone = "13987654321" },
                new Attendee { Name = "王五", Email = "wangwu@example.com", Phone = "13712345678" }
            };

            context.Attendees.AddRange(attendees);
            context.SaveChanges();

            // Add sample parties
            var parties = new List<Party>
            {
                new Party { Name = "新年派对", Location = "上海", Date = DateTime.Parse("2023-12-31") },
                new Party { Name = "春节联欢会", Location = "北京", Date = DateTime.Parse("2024-02-10") },
                new Party { Name = "中秋晚会", Location = "广州", Date = DateTime.Parse("2024-09-17") }
            };

            context.Parties.AddRange(parties);
            context.SaveChanges();

            // Add sample RSVPs
            var rsvps = new List<AttendeeParty>
            {
                new AttendeeParty { AttendeeId = attendees[0].Id, PartyId = parties[0].Id },
                new AttendeeParty { AttendeeId = attendees[0].Id, PartyId = parties[1].Id },
                new AttendeeParty { AttendeeId = attendees[1].Id, PartyId = parties[0].Id },
                new AttendeeParty { AttendeeId = attendees[2].Id, PartyId = parties[2].Id }
            };

            context.AddRange(rsvps);
            context.SaveChanges();
        }
    }
} 