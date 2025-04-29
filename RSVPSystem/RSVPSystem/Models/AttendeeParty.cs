namespace RSVPSystem.Models
{
    public class AttendeeParty
    {
        // 外键
        public int AttendeeId { get; set; }
        // 导航
        public Attendee Attendee { get; set; } = null!;

        public int PartyId { get; set; }
        public Party Party { get; set; } = null!;
    }
} 