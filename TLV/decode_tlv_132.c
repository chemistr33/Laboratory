void
decode_tlv_132(char *tlv_ptr)
{
    int tlv_type = (int)*(tlv_ptr);              // read 1st byte, the type
    tlv_ptr++;                                   // move to next byte
    int tlv_len = (int)*(tlv_ptr);               // read 2nd byte, the length
    int unit_tlv_size = get_init_size(tlv_type); // it will be a constant = 5, for TLV132*
    int i = 0;
    tlv_ptr++; // move the tlv_ptr to point to the start of the actual data
    char ip_address[4];
    switch (tlv_type)
    {
    case 132:
    {
        int n_units = tlv_len / unit_tlv_size; // number of units
        for (i = 0; i < n_units; i++)
        {

            memcpy(ip_address, tlv_ptr, 4);

            tlv_ptr += 4;         // move to next unit
            char mask = *tlv_ptr; // read 1 byte, the mask
            tlv_ptr++;            // move to next byte
        }
    }
    break;
    default:
        tlv_ptr += tlv_len; // move to next tlv
        break;
    }
}
