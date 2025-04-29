namespace RSVPSystem.Models
{
    public class AttendeeParty
    {
        public int AttendeeId { get; set; }
        public Attendee Attendee { get; set; } = null!;

        public int PartyId { get; set; }
        public Party Party { get; set; } = null!;
    }
} 