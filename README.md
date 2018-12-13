# file_safe
file encryption and decryption utility


  an encrypted file :
  
  file_header             one block                                   and several other blocks ...                    the last block tends to smaller than 10M
  _____________________   ________________________________________                                    ________________________________________         ________________________________________ 
  |num of blocks| 8bytes| |block header(encrypted)  | 128 bytes   |                                   |block header(encrypted)  | 128 bytes   |       |content data(original )  | <128*2 B    |
  |_____________|______ | |_________________________|_____________|                                   |_________________________|_____________|       |_________________________|_____________|
                          | content data (original) |10M - 128*2B |                                   | content data (original) |all left data|  or 
                          |_________________________|_____________|     ...   ...                     |_________________________|_____________|
                          |block tail (encrypted)   | 128 B       |                                   |block tail (encrypted)   | 128 B       |
                          |_________________________|_____________|                                   |_________________________|_____________|


