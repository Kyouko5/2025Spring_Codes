using Microsoft.EntityFrameworkCore;
using RSVPSystem.Models;

namespace RSVPSystem.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }

        public DbSet<Attendee> Attendees { get; set; } = null!;
        public DbSet<Party> Parties { get; set; } = null!;

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Configure many-to-many relationship
            modelBuilder.Entity<AttendeeParty>()
                .HasKey(ap => new { ap.AttendeeId, ap.PartyId });

            // 多对多拆分成两个一对多
            modelBuilder.Entity<AttendeeParty>()
                .HasOne(ap => ap.Attendee)
                .WithMany(a => a.AttendeeParties)
                .HasForeignKey(ap => ap.AttendeeId);

            modelBuilder.Entity<AttendeeParty>()
                .HasOne(ap => ap.Party)
                .WithMany(p => p.AttendeeParties)
                .HasForeignKey(ap => ap.PartyId);
        }
    }
} 