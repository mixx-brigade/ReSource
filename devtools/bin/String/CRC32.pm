package String::CRC32;

use strict;
use warnings;
use Exporter 'import';

our @EXPORT = qw(crc32);

my @crc_table = ();
for my $i (0 .. 255) {
    my $c = $i;
    for (1 .. 8) {
        if ($c & 1) {
            $c = 0xEDB88320 ^ ($c >> 1);
        } else {
            $c = $c >> 1;
        }
    }
    $crc_table[$i] = $c;
}

sub crc32 {
    my ($data) = @_;
    my $crc = 0xFFFFFFFF;

    if (defined($data) && (fileno($data) || ref($data) eq 'GLOB')) {
        # Filehandle / Glob
        my $pos = tell($data);
        seek($data, 0, 0);
        my $buffer;
        while (read($data, $buffer, 4096)) {
            for my $char (unpack('C*', $buffer)) {
                $crc = $crc_table[($crc ^ $char) & 0xFF] ^ ($crc >> 8);
            }
        }
        if (defined $pos && $pos >= 0) {
            seek($data, $pos, 0);
        }
    } else {
        # String
        my $str = defined($data) ? "$data" : "";
        for my $char (unpack('C*', $str)) {
            $crc = $crc_table[($crc ^ $char) & 0xFF] ^ ($crc >> 8);
        }
    }
    return $crc ^ 0xFFFFFFFF;
}

1;
